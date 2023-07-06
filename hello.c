#include "postgres.h"
#include "fmgr.h"
#include "tcop/utility.h"

#include "utils/builtins.h"

char *message = "hello, c world!";
const char* need = "create table";
static ProcessUtility_hook_type prev_ProcessUtility = NULL;
static int counter;

PG_MODULE_MAGIC;

Datum hello_cworld(PG_FUNCTION_ARGS);

PG_FUNCTION_INFO_V1(hello_cworld);

Datum
hello_cworld(PG_FUNCTION_ARGS)
{
    PG_RETURN_INT32(counter);
}

static void pgss_ProcessUtility(PlannedStmt *pstmt, const char *queryString,
                                bool readOnlyTree,
                                ProcessUtilityContext context, ParamListInfo params,
                                QueryEnvironment *queryEnv,
                                DestReceiver *dest, QueryCompletion *qc);

void
_PG_init()
{   
    counter = 0;
    prev_ProcessUtility = ProcessUtility_hook;
    ProcessUtility_hook = pgss_ProcessUtility;
}


static void
pgss_ProcessUtility(PlannedStmt *pstmt, const char *queryString,
                    bool readOnlyTree,
                    ProcessUtilityContext context,
                    ParamListInfo params, QueryEnvironment *queryEnv,
                    DestReceiver *dest, QueryCompletion *qc)
{
   if (prev_ProcessUtility != NULL){
                prev_ProcessUtility(pstmt, queryString, readOnlyTree,
                                    context, params, queryEnv,
                                    dest, qc);
    }else{
        standard_ProcessUtility(pstmt, queryString, readOnlyTree,
                                        context, params, queryEnv,
                                        dest, qc);
    }
   
   elog(LOG, "Hi");
   elog(LOG, queryString);
   int result = strncasecmp(queryString, need, strlen(need));
   if(result == 0){
      elog(LOG, "asdasd ===========================");
      counter++;
   }
}