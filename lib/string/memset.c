#include <string.h>
#include <stdlib.h>
#include <stddef.h>

void *memset(void *ptr, int val, size_t n)
{
	unsigned char *p = (unsigned char *)ptr;
	while (n--)
		*p++ = (unsigned char)val;
	return ptr;
}
