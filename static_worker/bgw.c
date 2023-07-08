#include "postgres.h"

#include "fmgr.h"
#include "postmaster/bgworker.h"

PG_MODULE_MAGIC

PGDLLEXPORT void bgw1_main(Datum main_arg);

void _PG_init(void){
	BackgroundWorker worker;
	memset(&worker, 0, sizeof(worker));
	worker.bgw_flags = BGWORKER_SHMEM_ACCESS;
	worker.bgw_start_time = BgWorkerStart_RecoveryFinished;
	worker.bgw_restart_time = BGW_NEVER_RESTART;
	sprintf(worker.bgw_library_name, "bgw1");

	sprintf(worker.bgw_function_name, "bgw1_main");
	sprintf(worker.bgw_name, "bgw1 worker");

	elog(LOG, "register bgw1");
	sprintf(worker.bgw_type, "bgw1");

	RegisterBackgroundWorker(&worker);

}

void bgw1_main(Datum main_arg){
	for(int i = 0; i < 10; i++){
		elog(LOG, "bgw1 iteration %d", i);
		pg_usleep(1000000L);
	}
}