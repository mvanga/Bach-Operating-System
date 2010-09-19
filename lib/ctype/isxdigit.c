#include <ctype.h>

int __isxdigit_ascii(int ch);
int __isxdigit_ascii(int ch)
{
	return (unsigned int)( ch         - '0') < 10u  || 
	       (unsigned int)((ch | 0x20) - 'a') <  6u;
}

int isxdigit ( int ch )
{
	return __isxdigit_ascii(ch);
}
