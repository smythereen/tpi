/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2007-2026 John R. Smythe Jr. */
/*******************************************************************************
 * 
 *	The Transactions Per Interval (TPI) Parameters - Shared Memory Format
 ******************************************************************************/
#include	<map.h>
#include	<mem_io.h>
#include	<tpi.h>

extern	Mitem		tpi_l[ ];

static	void	usage( char * av[ ] )
{
	fprintf( stderr,
		 "\nUsage:\n"
			"\t%s tpi_file.mem [ C.Variable.Name [ Value ] ]\n\n",
			 av[ 0 ]
	);
	fflush( stderr );
	exit( 1 );
}

int	main( int ac, char * av[ ] )
{
	tpi_t	*	tpi;
	char		buf[ 256 ];

	switch( ac ) {
	case 2:		break;
	default:	if( isalpha( *av[2] ) ) break;
	case 1:
	case 0:		usage( av );
			return( 1 );
	}
	LocalName = av[0];

	tpi = MapFile2Mem( av[1], sizeof( tpi_t ), PROT_WRITE );
	if( tpi == NULL ) {
		fprintf( stderr, "\nCannot Map File \"%s\"\n", av[1] );
		fflush( stderr );
		usage( av );
		return( 1 );
	}

	if( *LocalName == 'T' ) {
		av[0] = 0;
	} else {
		sprintf( buf, "%s \"%s\"", av[0], av[1] );
		av[0] = buf;
	}

	switch( ac ) {
	default:   Input_Memory_Item(  tpi, tpi_l, av[2], av[3] );
		   UpdateMap( tpi, sizeof( tpi_t ) );
	case  3:   Output_Memory_Item( tpi, tpi_l, av[2], av[0] );
		   break;
	case  2:   Output_Memory_Item( tpi, tpi_l,     0, av[0] );
		   break;
	}
	UnmapAddress( tpi, 1 );
	exit( 0 );
}
