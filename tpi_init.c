/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2007-2026 John R. Smythe Jr. */
/*******************************************************************************
 * 
 *	Calculate Transactions Per Interval 
 *
 *	This file defines the following puplic functions.
 *		TPI_Initialize( );
 ******************************************************************************/
#include	<tpi.h>

void	TPI_Initialize( tpi_t * tpi, u32 interval, char * file )
{
	tpi->Interval = interval;	/* Interval In Seconds */
	tpi->Count = 0;			/* Current Count */
	tpi->Maximum = 0;		/* Maximum Count Seen This Interval */
	tpi->Limit = 0;			/* Count's Cannot Exceed Limit (0=No Limit) */
	tpi->Total = 0;			/* Total Increments Seen This Interval */
	tpi->Stamp = 0;			/* Next Interval's Date & Time */
	memset( tpi->File, 0, sizeof( tpi->File ) );
	if( file == NULL || *file == 0 ) return;
	strncpy( tpi->File, file, sizeof( tpi->File ) );
}
