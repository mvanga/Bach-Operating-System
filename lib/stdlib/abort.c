#include <stdlib.h>
#include <klib_glue.h>

void abort(void)
{
	_glue_exit(127);
}
