#include <string.h>
#include <stdlib.h>
#include <stddef.h>

char *strncpy(char *s1, const char *s2, size_t n)
{
	char *dst = s1;
	const char *src = s2;
	while (n > 0) {
		n--;
		if ((*dst++ = *src++) == '\0') {
			memset(dst, '\0', n);
			break;
		}
	}
	return s1;
}
