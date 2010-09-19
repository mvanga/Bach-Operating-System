#include <string.h>
#include <stdlib.h>
#include <stddef.h>

char *strpbrk(const char *s1, const char *s2)
{
	const char *sc1;
	for (sc1 = s1; *sc1 != '\0'; sc1++)
		if (strchr(s2, *sc1) != NULL)
			return (char *)sc1;
	return NULL;
}
