#include <klib_glue.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

void *realloc(void *buf, size_t new_size)
{
	if (buf == 0)
		return malloc(new_size);
	return _glue_realloc(buf, new_size);
}
