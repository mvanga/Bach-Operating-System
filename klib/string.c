#include <bach/string.h>
#include <klib/stdlib.h>
#include <klib/stddef.h>

int kstrlen(char *str)
{
	int len = 0;
	while(*str++)
		len++;
	return len;
}
