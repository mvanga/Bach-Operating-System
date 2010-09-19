#include <string.h>
#include <stddef.h>

void *memmove(void *s1, const void *s2, size_t n)
{
	char *p1 = s1;
	const char *p2 = s2;
	if (p2 < p1 && p1 < p2 + n) {
		p2 += n;
		p1 += n;
		while (n-- != 0) 
			*--p1 = *--p2;
	} else {
		while (n-- != 0) 
			*p1++ = *p2++;
	}
	return s1;
}
