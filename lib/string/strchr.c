#include <string.h>
#include <stdlib.h>
#include <stddef.h>

char *strchr(const char *s, int c)
{
	while (*s != '\0' && *s != (char)c)
		s++;
	return ( (*s == c) ? (char *) s : NULL );
}
