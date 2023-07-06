#include "postgres.h"
#include "fmgr.h"

#include "utils/builtins.h"

char *message = "hello, c world!";

PG_MODULE_MAGIC;

Datum hello_cworld(PG_FUNCTION_ARGS);

PG_FUNCTION_INFO_V1(hello_cworld);

Datum
hello_cworld(PG_FUNCTION_ARGS)
{
    PG_RETURN_TEXT_P(cstring_to_text(message));
}

void
_PG_init()
{
    elog(LOG, "hello world!");
}
