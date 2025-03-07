/*-------------------------------------------------------------------------
 *
 * pg_rewind.h
 *
 *
 * Portions Copyright (c) 1996-2023, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 *-------------------------------------------------------------------------
 */
#ifndef PG_REWIND_H
#define PG_REWIND_H

#include "access/timeline.h"
#include "common/logging.h"
#include "datapagemap.h"
#include "fe_utils/simple_list.h"
#include "libpq-fe.h"
#include "pg_rewind_ext.h"
#include "storage/block.h"
#include "storage/relfilelocator.h"

/* Configuration options */
extern char *datadir_target;
extern bool showprogress;
extern bool dry_run;
extern bool do_sync;
extern int	WalSegSz;

/* Target history */
extern TimeLineHistoryEntry *targetHistory;
extern int	targetNentries;

/* Progress counters */
extern uint64 fetch_size;
extern uint64 fetch_done;

/* in parsexlog.c */
extern void extractPageMap(const char *datadir, XLogRecPtr startpoint,
						   int tliIndex, XLogRecPtr endpoint,
						   const char *restoreCommand);
extern void findLastCheckpoint(const char *datadir, XLogRecPtr forkptr,
							   int tliIndex,
							   XLogRecPtr *lastchkptrec, TimeLineID *lastchkpttli,
							   XLogRecPtr *lastchkptredo,
							   const char *restoreCommand);
extern XLogRecPtr readOneRecord(const char *datadir, XLogRecPtr ptr,
								int tliIndex, const char *restoreCommand);

/* in pg_rewind.c */
extern void progress_report(bool finished);

/* in timeline.c */
extern TimeLineHistoryEntry *rewind_parseTimeLineHistory(char *buffer,
														 TimeLineID targetTLI,
														 int *nentries);

/* in extension.c */
extern void process_extensions(SimpleStringList *extensions,
							   const char *datadir_target, char *datadir_source,
							   char *connstr_source, XLogRecPtr startpoint,
							   int tliIndex, XLogRecPtr endpoint,
							   const char *restoreCommand, const char *argv0,
							   bool debug);

#endif							/* PG_REWIND_H */
