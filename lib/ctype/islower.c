#include <ctype.h>

int __islower_ascii(int ch);
int __islower_ascii(int ch) {
    return (unsigned int) (ch - 'a') < 26u;
}

int islower(int ch)
{
	return __islower_ascii(ch);
}
