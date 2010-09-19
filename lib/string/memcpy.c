#include <string.h>

void *memcpy(void * s1, const void * s2, size_t n)
{
	char *dst = s1;
	const char *src = s2;
	while (n-- != 0)
		*dst++ = *src++;
	return s1;
}

