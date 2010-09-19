#include <string.h>
#include <stdlib.h>
#include <stddef.h>

void *memchr(const void *s, char c, size_t n)
{
	const unsigned char *src = s;
	unsigned char uc = c;
	while (n-- != 0) {
		if (*src == uc)
			return (void *) src;
		src++;
	}
	return NULL;
}
