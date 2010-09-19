#include <string.h>
#include <stdlib.h>
#include <stddef.h>

char *strcpy(char *toHere, const char *fromHere)
{
	int i = 0;
	while ((toHere[i] = fromHere[i++]));
	return toHere;
}
