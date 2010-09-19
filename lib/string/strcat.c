#include <string.h>
#include <stdlib.h>
#include <stddef.h>

char *strcat(char *dest, const char *src)
{
	char *p = dest;
	while (*p++ != 0);
	while (*src != 0)
		*p++ = *src++;
	return dest;
}
