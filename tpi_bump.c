/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2007-2026 John R. Smythe Jr. */
/*******************************************************************************
 * 
 *	Calculate Transactions Per Interval 
 *
 *	This file defines the following puplic functions.
 *		TPI_Bump( );
 ******************************************************************************/
#include	<tpi.h>
#include	<atomic_32.h>

int	TPI_Bump( tpi_t * tpi, s32 val, u32 limit )
{
	s64	a;

	if( tpi->Interval > 0 ) TPI_Check( tpi );

	if( limit > 0 ) tpi->Limit = limit;

	a = S32_Add_Return( val, &tpi->Count );
	if( a > tpi->Maximum ) tpi->Maximum = a;
	if( val > 0 ) S32_Add( val, &tpi->Total );

	if( tpi->Limit > 0 && tpi->Limit < a ) {
		if( tpi->Threshold > 0 && tpi->File[ 0 ] != 0 && tpi->Limit >= tpi->Threshold ) {
			EventLog(
				"%s Threshold=%u, Current=%u, Hit Upper Limit=%u",
				tpi->File,
				tpi->Threshold,
				a,
				tpi->Limit
			);
		}
		return( 0 );	// Exceeded Limit
	}

	if( tpi->Threshold > 0 && tpi->File[ 0 ] != 0 && a >= tpi->Threshold ) {
		EventLog(
			"%s Exceeded Threshold=%u, Current=%u, Upper Limit=%u",
			tpi->File,
			tpi->Threshold,
			a,
			tpi->Limit
		);
	}
	return( 1 );
}
