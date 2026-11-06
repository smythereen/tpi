/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2007-2026 John R. Smythe Jr. */
/*******************************************************************************
 * 
 *	Transactions Per Interval (TPI) Memory Format Data
 ******************************************************************************/
#include	<mem_io.h>
#include	<tpi.h>

/*
 *	tpi_l
 */

#define	STRUCT	tpi_t
	Mitem		tpi_l[ ] =	{
	Ulong(		Interval,	"Interval In Seconds (0=No Interval)"	),
	Ulong(		Count,		"Current Count"				),
	Ulong(		Maximum,	"Maximum Count Seen This Hour"		),
	Ulong(		Limit,		"Count Never Exceeds Non-Zero Limit"	),
	Ulong(		Total,		"Total Count Increments For This Hour"	),
	Stamp(		Stamp,		"Start Of Next Hour"			),
	Ulong(		Threshold,	"Minimum Threshold For SNMP/EventLog"	),
	String(		File,		"Hourly Data [ Path & ] File"		),
	{ END_OF_LIST }
};
#undef	STRUCT
