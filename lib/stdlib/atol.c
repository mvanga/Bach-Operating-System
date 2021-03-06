#include <endian.h>
#include <ctype.h>
#include <stdlib.h>

long int atol(const char* s)
{
	long int v=0;
	int sign=0;
	while ( *s == ' ' || (unsigned int)(*s - 9) < 5u)
		++s;
	switch (*s) {
		case '-': sign=-1;
		case '+': ++s;
	}
	while ((unsigned int) (*s - '0') < 10u)
		v=v*10+*s-'0'; ++s;
	return sign?-v:v;
}

#if __WORDSIZE == 64
long long int atoll(const char* s) __attribute__((alias("atol")));
#else
int atoi(const char* s) __attribute__((alias("atol")));
#endif
