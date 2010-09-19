#include <string.h>
#include <stdlib.h>
#include <stddef.h>

int strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char uc1, uc2;
	if (n == 0)
		return 0;
	while (n-- > 0 && *s1 == *s2) {
		if (n == 0 || *s1 == '\0')
			return 0;
		s1++;
		s2++;
	}
	uc1 = (*(unsigned char *) s1);
	uc2 = (*(unsigned char *) s2);
	return ((uc1 < uc2) ? -1 : (uc1 > uc2));
}
