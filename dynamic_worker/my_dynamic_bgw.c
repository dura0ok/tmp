#include "postgres.h"
#include "fmgr.h"

#include "miscadmin.h"
#include "postmaster/bgworker.h"
#include "postmaster/interrupt.h"
#include "storage/ipc.h"
#include "storage/latch.h"
#include "storage/lwlock.h"
#include "storage/proc.h"
#include "storage/shmem.h"

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(my_dynamic_bgw);

PGDLLEXPORT void my_bgw_dynamic_main(Datum main_arg);

void
my_bgw_dynamic_main(Datum main_arg)
{
BackgroundWorkerUnblockSignals();

for(int i = 0; i < 100; ++i){
elog(LOG, "iteration %d", i);
pg_usleep(1000000L);
}
}

Datum
my_dynamic_bgw(PG_FUNCTION_ARGS)
{
BackgroundWorker worker;

memset(&worker, 0, sizeof(worker));
worker.bgw_flags = BGWORKER_SHMEM_ACCESS;
worker.bgw_start_time = BgWorkerStart_RecoveryFinished;
worker.bgw_restart_time = BGW_NEVER_RESTART;
sprintf(worker.bgw_library_name, "my_bgw");
sprintf(worker.bgw_function_name, "my_bgw_main");
sprintf(worker.bgw_name, "my_bgw_dynamic");
sprintf(worker.bgw_type, "my_bgw");

if(!RegisterDynamicBackgroundWorker(&worker, NULL))
elog(ERROR, "Couldn't register worker");

PG_RETURN_VOID();
}

void
_PG_init(void)
{
elog(LOG, "initialising my_bgw(dynamic)");
}