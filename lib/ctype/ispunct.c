#include <ctype.h>

int __ispunct_ascii(int ch);
int __ispunct_ascii(int ch)
{
	return isprint (ch)  &&  !isalnum (ch)  &&  !isspace (ch);
}

int ispunct(int ch)
{
	return __ispunct_ascii(ch);
}
