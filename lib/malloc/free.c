#include <klib_glue.h>
#include <stdlib.h>

void free(void *chunk_ptr)
{
	if (! chunk_ptr)
		return;
	_glue_free(chunk_ptr);
}

