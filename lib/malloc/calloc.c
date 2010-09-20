#include <assert.h>
#include <malloc.h>
#include <string.h>

void *calloc(size_t nelt, size_t eltsize)
{
	size_t allocsize = nelt * eltsize;

	void *ptr = malloc(allocsize);
	if (!ptr)
		return 0;

	memset(ptr, 0, allocsize);

	return ptr;
}
