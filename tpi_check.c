/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2007-2026 John R. Smythe Jr. */
/*******************************************************************************
 * 
 *	Calculate Transactions Per Interval 
 *
 *	This file defines the following puplic functions.
 *		TPI_Check( );
 ******************************************************************************/
#include	<sys/time.h>
#include	<tpi.h>
#include	<atomic_32.h>

int	TPI_Check( tpi_t * tpi )
{
	u32	a;
	time_t	now;

	if( tpi->Interval == 0 ) return( 0 );
	if( (u32)time( &now ) < tpi->Stamp ) return( 0 );
	do{
		a = S32_Add_Return( tpi->Interval, &tpi->Stamp );
		TPI_Interval( tpi );
	} while( a <= (u32)now );


	/*
	 *	Set Stamp To Begining Of Next Interval
	 */

	tpi->Stamp = ( ( (u32)now / tpi->Interval ) * tpi->Interval ) + tpi->Interval;
	return( 1 );
}
