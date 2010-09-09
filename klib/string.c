#include <bach/string.h>

int kstrlen(char *str)
{
	int len = 0;
	while(*str++)
		len++;
	return len;
}
