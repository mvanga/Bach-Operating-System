#include <ctype.h>

int __isspace_ascii(int ch);
int __isspace_ascii(int ch)
{
	return (unsigned int)(ch - 9) < 5u  ||  ch == ' ';
}

int isspace(int ch)
{
	return __isspace_ascii(ch);
}
