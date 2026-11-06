# tpi — transactions per interval, with limit and threshold

`tpi` is a single **interval counter with an upper limit**, kept in a
memory-mapped `tpi_t`. It counts up and down (for example, calls in progress),
tracks the maximum and the total of positive increments for the interval, and
refuses to go past `Limit`. It writes an `EventLog` entry when `Threshold` or
`Limit` is reached. At the end of each `Interval` it writes a line to its data
`File` and resets. Several processes can update the same mapped counter;
updates use `atomic` operations (`S32_Add_Return`, `S32_Add`).

## Structure (`tpi.h`)

```c
typedef struct tpi_s {
    u32  Interval;   /* Interval Period For File Dump & Var Reset */
    s32  Count;      /* The Count For The Current Interval */
    u32  Maximum;    /* Maximum Count Seen In The Interval */
    u32  Limit;      /* The Count Cannot Exceed This Limit */
    u32  Total;      /* Total Positive Counts For The Current Interval */
    u32  Stamp;      /* Next Interval's Date & Time */
    u32  Threshold;  /* Minimum SNMP/EventLog Alarm Threshold */
    char File[ 60 ]; /* Data File To Store The Interval Counts */
} tpi_t;
```

## How a client uses it

- `TPI_Initialize(tpi, interval_seconds, data_file)`
- `TPI_Bump(tpi, val, limit)`: add `val` (+1 or -1). Returns 0 when the new
  count exceeds `Limit`, so the caller can refuse work. A non-zero `limit`
  replaces `Limit`.
- `TPI_Check(tpi)`: close the interval when the clock passes `Stamp`.
- `TPI_Interval(tpi)`: force the end-of-interval write and reset.

## Utility programs and scripts

- `tpi FILE.mem b[ump] [±1 [limit]] | c[heck] | i[nitialize] [secs [file.csv]] | int[erval]`
- `tpimem FILE.mem [field [value]]`: view or set fields through `mio` (`tpi_l` table).
- `call_look.sh` / `call_stat.sh`: sample scripts that read and set the
  `fixed.side[N].calls` `tpi_t` fields with a `tgnmem` tool. That tool is not in
  any public unit, so the scripts are only examples of the field names.

This unit has no test suite. Output from a manual gcc build of this source
(not the `make` build):

```
$ tpi

	Transactions Per Interval (TPI) - Utility Program

Usage:
	tpi	tpi.mem b[ump]       [ +/-1 [ Upper_Limit ] ]
	  	tpi.mem c[heck]
	  	tpi.mem i[nitialize] [ Interval_Seconds [ IntervalDataFile.csv ] ]
	  	tpi.mem int[erval]

$ tpi tpi.mem initialize 60 tpi.csv
Interval=60
File=tpi.csv
```

## Environment

`map` and `sys` resolve mapped files through the base run paths
(`MEMORY_PATH`, `FILE_PATH` and `DATA_PATH`, all `$HOME/run/` in
`env.example`). `EventLog` writes to `ELOG_FILE`. `MEMORY_ALL` affects
`tpimem` (see `mio`).

## Dependencies

| Unit | Kind | Evidence |
|------|------|----------|
| `sys` | direct | `tpi.h` includes `<common.h>`; `EventLog` |
| `atomic` | direct (header only) | `tpi_bump.c` and `tpi_check.c` include `<atomic_32.h>` |
| `far` | direct | `tpi_interval.c` includes `<far.h>` |
| `map` | direct | `tpi.c` and `tpimem.c` call `MapFile2Mem`, `UpdateMap` and `UnmapAddress` |
| `mio` | direct | `tpi_l.c` and `tpimem.c` include `<mem_io.h>` |
| `sem` | indirect (link) | `map/unmap.c` calls `SemFree`; linking `tpimem` without `-lsem` fails with `undefined reference to SemFree` |
| `now` | indirect (link) | required by `mio` |

Makefile: `LIBRARIES = -lmio -lmap -lsem -lfar -lnow -lsys`. `UNIT.deps` lists
`far map mio now sem sys`. No `msg` or `addr` unit is used.

## Getting it

Requires the `base` repository (project root with `BASE`, `rules.mak`,
`targets.mak` and the `repo` unit). A plain `make` in a fresh base clone
fetches the starter list (project `NONE`), which is, in dependency order:

```
sys atomic far map sem now mio tp tpi
```

Or add this unit on its own with `repo add <unit>`.

## License

The original files are offered under `Apache-2.0 OR GPL-2.0-or-later`;
you choose either license. See `LICENSE` and `LICENSES/`. Copyright notices
are retained; third-party-derived files keep their own SPDX identifiers.

## Version

Version tag: `v0.2.0`.
