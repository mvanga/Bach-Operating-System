#include <string.h>
#include <stdlib.h>
#include <stddef.h>

int strcmp(const char *s1, const char *s2)
{
	unsigned char uc1, uc2;
	while (*s1 != '\0' && *s1 == *s2) {
		s1++;
		s2++;
	}
	uc1 = (*(unsigned char *) s1);
	uc2 = (*(unsigned char *) s2);
	return ((uc1 < uc2) ? -1 : (uc1 > uc2));
}
