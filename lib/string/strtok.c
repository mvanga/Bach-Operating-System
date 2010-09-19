#include <string.h>
#include <stdlib.h>
#include <stddef.h>

char *strtok_r(char *s, const char *delimiters, char **lasts)
{
	char *sbegin, *send;
	sbegin = s ? s : *lasts;
	sbegin += strspn(sbegin, delimiters);
	if (*sbegin == '\0') {
		*lasts = "";
		return NULL;
	}
	send = sbegin + strcspn(sbegin, delimiters);
	if (*send != '\0')
		*send++ = '\0';
	*lasts = send;
	return sbegin;
}
