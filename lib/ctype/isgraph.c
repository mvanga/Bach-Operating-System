#include <ctype.h>

int __isgraph_ascii(int ch);
int __isgraph_ascii(int ch) {
	return (unsigned int)(ch - '!') < 127u - '!';
}

int isgraph(int ch)
{
	return __isgraph_ascii(ch);
}
