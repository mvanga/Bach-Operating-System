#include <assert.h>

void __assert_fail (const char *__assertion, const char *__file,
			   unsigned int __line, const char *__function)
{
	char *a = (char *)__assertion;
	char *b = (char *)__file;
	char *c = (char *)__line;
	char *d = (char *)__function;
	a = b;
	c = d;
	for(;;);
}
