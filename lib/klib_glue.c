#include <klib_glue.h>

void _glue_exit(int ret)
{
	ret = 0;
}

void *_glue_alloc(size_t size)
{
	size = 0;
	return NULL;
}

void *_glue_alloc_align(size_t size, size_t align)
{
	size = 0;
	align = 0;
	return NULL;
}

void *_glue_realloc(void *ptr, size_t new_size)
{
	ptr = NULL;
	new_size = 0;
	return NULL;
}
