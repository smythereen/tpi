/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2007-2026 John R. Smythe Jr. */
/*******************************************************************************
 * 
 *	Transactions Per Interval (TPI) Utility
 ******************************************************************************/
#include	<tpi.h>
#include	<map.h>
#include	<string.h>

static	tpi_t	*	tpi;

static	void	bump( int ac, char *av[ ] )
{
	int	val = 1;
	u32	limit = 0;

	switch( ac ) {
	default:
	case 2:	limit	= strtoul( av[ 1 ], 0, 10 );
	case 1:	val	= strtol(  av[ 0 ], 0, 10 );
	}

	if( TPI_Bump( tpi, val, limit ) ) {
		printf(	"Count=%u\n", tpi->Count );
	} else {
		printf(	"Count=Limit %u Execeeded\n", limit );
	}
	exit( 0 );
}

static	void	check( int ac, char *av[ ] )
{
	if( TPI_Check( tpi ) ) {
		printf(	"New Hour\n" );
		exit( 1 );
	}
	printf(	"Old Hour\n" );
	exit( 0 );
}

static	void	initialize( int ac, char *av[ ] )
{
	char *	file = NULL;
	u32	interval = 0;

	switch( ac ) {
	default:
	case 2:	file		= av[ 1 ];
	case 1:	interval	= strtoul( av[ 0 ], 0, 10 );
	}

	TPI_Initialize( tpi, interval, file );
	printf(	"Interval=%u\n", tpi->Interval );
	printf(	"File=%0.64s\n", tpi->File );
	exit( 0 );
}

static	void	interval( int ac, char *av[ ] )
{
	printf(	"Old Stamp=%u\n", tpi->Stamp );
	TPI_Interval( tpi );
	printf(	"New Stamp=%u\n", tpi->Stamp );
	printf(	"Interval=%u\n", tpi->Interval );
	exit( 0 );
}

static	struct	list_s	{
	char *	cmd;
	void (*func)( int ac, char *av[ ] );
}	list[ ]	=	{
	{	"bump",			bump		},
	{	"check",		check		},
	{	"initialize",		initialize	},
	{	"interval",		interval	},
	{	(char *)0,		(void (*)( int, char ** ))0	}
};

static	void	usage( char * av[ ] )
{
	fprintf( stderr,
		 "\n\tTransactions Per Interval (TPI) - Utility Program\n\n"
		 "Usage:\n"
		 "\t%s\ttpi.mem b[ump]       [ +/-1 [ Upper_Limit ] ]\n"
		 "\t  \ttpi.mem c[heck]      \n"
		 "\t  \ttpi.mem i[nitialize] [ Interval_Seconds [ IntervalDataFile.csv ] ]\n"
		 "\t  \ttpi.mem int[erval]   \n"
		 "\n",
		 av[ 0 ]
	);
	fflush( stderr );
	exit( 2 );
}

int	main( int ac, char * av[ ] )
{
struct	list_s	*	l;
	int		len;

	LocalName = av[ 0 ];

//	TraceLevel = TPI_TRC_LVL;

	switch( ac ) {
	default:
		tpi = MapFile2Mem( av[1], sizeof( tpi_t ), PROT_WRITE );
		if( tpi != NULL ) {
			len = strlen( av[ 2 ] );
			for( l = list; l->cmd != (char *)0; l++ ) {
				if( strncasecmp( av[ 2 ], l->cmd, len ) ) continue;
				l->func( ( ac - 3 ), &av[ 3 ] );
				exit( 0 );
			}
		} else {
			fprintf( stderr, "\nCannot Map File \"%s\"\n", av[1] );
			fflush( stderr );
		}
	case  2:
	case  1:
	case  0:	usage( av );
	}
	exit( 0 );
}
