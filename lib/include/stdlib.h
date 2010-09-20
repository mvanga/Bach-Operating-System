#ifndef __KLIB_STDLIB_H__
#define __KLIB_STDLIB_H__

#include <stddef.h>

void *calloc(size_t nmemb, size_t size);
void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);

char *getenv(const char *name);
int putenv(const char *string);

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
extern int rand_r(unsigned int *seed);
extern void srand(unsigned int seed);

typedef unsigned short randbuf[3];
double drand48(void);
long lrand48(void);
long mrand48(void);
void srand48(long seed);
unsigned short *seed48(randbuf buf);
void lcong48(unsigned short param[7]);
long jrand48(randbuf buf);
long nrand48(randbuf buf);
double erand48(randbuf buf);

void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));
void *bsearch(const void *key, const void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));

extern char **environ;
extern void *klibc_mem;

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define RAND_MAX 	0x7ffffffe

#define MB_CUR_MAX 1

typedef struct { int quot,rem; } div_t;
typedef struct { long quot,rem; } ldiv_t;

div_t div(int numerator, int denominator);
ldiv_t ldiv(long numerator, long denominator);

#endif
