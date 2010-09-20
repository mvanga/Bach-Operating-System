#include <klib_glue.h>
#include <stddef.h>
#include <stdlib.h>

void *malloc(size_t size)
{
	return _glue_alloc(size);
}

