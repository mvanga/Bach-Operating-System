#include <string.h>
#include <stdlib.h>
#include <stddef.h>

int memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *us1 = (const unsigned char *) s1;
	const unsigned char *us2 = (const unsigned char *) s2;
	while (n-- != 0) {
		if (*us1 != *us2)
			return (*us1 < *us2) ? -1 : +1;
		us1++;
		us2++;
	}
	return 0;
}
