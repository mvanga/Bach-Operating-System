#include <klib_glue.h>
#include <stddef.h>
#include <stdlib.h>

void *memalign(size_t alignment, size_t size)
{
	return _glue_alloc_align(size, alignment);
}
