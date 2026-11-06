/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2007-2026 John R. Smythe Jr. */
/*******************************************************************************
 * 
 *	TPI (Transactions Per Interval) Header File
 *
 *	This file defines common structures, variables, and routines
 *	need for shared memory access.
 ******************************************************************************/
#ifndef	TPI_H
#define	TPI_H

#if	defined( __cplusplus )
extern	"C"	{
#endif

#include	<common.h>

#define	TPI_CHUNK		tpi->Interval		/* Seconds */
#define	MAX_TPI_INTERVAL	100			/* */

typedef	struct	tpi_s	{
	u32		Interval;	/* Interval Period For File Dump & Var Reset */
	s32		Count;		/* The Count For The Current Interval */
	u32		Maximum;	/* Maximum Count Seen In The Interval */
	u32		Limit;		/* The Count Cannot Exceed This Limit */
	u32		Total;		/* Total Positive Counts For The Current Interval */
	u32		Stamp;		/* Next Interval's Date & Time */
	u32		Threshold;	/* Minimum SNMP/EventLog Alarm Threshold */
	char		File[ 60 ];	/* Data File To Store The Interval Counts */
}	tpi_t;

typedef	tpi_t	*	tpi_p;

extern	int	TPI_Bump(	tpi_t *	tpi, s32 val, u32 limit );
extern	int	TPI_Check(	tpi_t *	tpi );
extern	void	TPI_Initialize(	tpi_t *	tpi, u32 interval, char * interval_data_file );
extern	void	TPI_Interval(	tpi_t *	tpi );

#if	defined( __cplusplus )
}
#endif

#endif
