#include <string.h>
#include <stdlib.h>
#include <stddef.h>

size_t strlen(const char *s)
{
	int len = 0;
	while (*s++)
		len++;
	return len;
}
