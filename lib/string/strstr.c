#include <string.h>
#include <stdlib.h>
#include <stddef.h>

char *strstr(const char *haystack, const char *needle)
{
	size_t needlelen;
	/* Check for the null needle case.  */
	if (*needle == '\0')
		return (char *) haystack;
	needlelen = strlen(needle);
	for (; (haystack = strchr(haystack, *needle)) != NULL; haystack++)
		if (strncmp(haystack, needle, needlelen) == 0)
			return (char *) haystack;
	return NULL;
}
