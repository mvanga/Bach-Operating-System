#ifndef __KLIB_STDLIB_H__
#define __KLIB_STDLIB_H__

#include <stddef.h>

void *calloc(size_t nmemb, size_t size);
void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);

char *getenv(const char *name);
int putenv(const char *string);

int system (const char * string);
int atexit(void (*function)(void));

double strtod(const char *nptr, char **endptr);
long int strtol(const char *nptr, char **endptr, int base);
unsigned long int strtoul(const char *nptr, char **endptr, int base);
long long int strtoll(const char *nptr, char **endptr, int base);
unsigned long long int strtoull(const char *nptr, char **endptr, int base);

int atoi(const char *nptr);
long int atol(const char *nptr);
double atof(const char *nptr);

void exit(int status);
void abort(void);

extern int rand(void);
extern void srand(unsigned int seed);

void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));
void *bsearch(const void *key, const void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));

extern char **environ;

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define RAND_MAX 	0x7ffffffe

#define MB_CUR_MAX 1

typedef struct { int quot,rem; } div_t;
typedef struct { long quot,rem; } ldiv_t;

div_t div(int numerator, int denominator);
ldiv_t ldiv(long numerator, long denominator);

int mbtowc(wchar_t *pwc, const char *s, size_t n);
int wctomb(char *s, wchar_t wc);
size_t mbstowcs(wchar_t *dest, const char *src, size_t n);
int mblen(const char* s,size_t n);

#endif
