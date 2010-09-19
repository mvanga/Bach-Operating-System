#include <ctype.h>

int __isdigit_ascii(int ch);
int __isdigit_ascii(int ch) {
	return (unsigned int)(ch - '0') < 10u;
}

int isdigit(int ch)
{
	return __isdigit_ascii(ch);
}
