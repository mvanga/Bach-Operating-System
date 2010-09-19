#include <string.h>
#include <stdlib.h>
#include <stddef.h>

char *strrchr(const char *s, int c)
{
	const char *last = NULL;
	if (c == '\0')
		return strchr(s, c);
	while ((s = strchr(s, c)) != NULL) {
		last = s;
		s++;
	}
	return (char *) last;
}
