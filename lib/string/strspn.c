#include <string.h>
#include <stdlib.h>
#include <stddef.h>

size_t strspn(const char *s1, const char *s2)
{
	const char *sc1;
	for (sc1 = s1; *sc1 != '\0'; sc1++)
		if (strchr(s2, *sc1) == NULL)
			return (sc1 - s1);
	return sc1 - s1;
}
