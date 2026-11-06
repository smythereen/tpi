/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2007-2026 John R. Smythe Jr. */
/*******************************************************************************
 * 
 *	Calculate Transactions Per Interval 
 *
 *	This file defines the following puplic functions.
 *		TPI_Interval( );
 ******************************************************************************/
#include	<tpi.h>
#include	<far.h>
#include	<time.h>

void	TPI_Interval( tpi_t * tpi )
{
	if( tpi->File[ 0 ] != 0 && tpi->Stamp != 0 ) {
		char	buf[ 256 ];
		/*
		 *	Add Interval Data To File
		 */
		strftime( buf, sizeof( buf ), "%F %T", localtime( (time_t *)&tpi->Stamp ) );
		Write_Line(
			tpi->File,
			"%s,%u,%u,%u,%u\n",
			buf,
			tpi->Count,
			tpi->Maximum,
			tpi->Limit,
			tpi->Total
		);
	}
	/*
	 *	Reset the Transactions Per Interval (TPI) Counters
	 */
	tpi->Total = 0; 
	tpi->Maximum = 0; 
}
