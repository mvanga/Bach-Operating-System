#ifndef __KLIB_STRING_H__
#define __KLIB_STRING_H__

#include <stddef.h>

extern int kstrlen(char *str);
extern void *memcpy(void *s1, const void *s2, size_t n);
extern void *memmove(void *s1, const void *s2, size_t n);
extern void *memchr(const void *s, char c, size_t n);
extern int memcmp(const void *s1, const void *s2, size_t n);
extern void *memset(void *ptr, int val, size_t n);
extern char *strcat(char *dest, const char *src);
extern char *strncat(char *dest, const char *src, size_t n);
extern char *strchr(const char *s, int c);
extern char *strrchr(const char *s, int c);
extern int strcmp(const char *s1, const char *s2);
extern int strncmp(const char *s1, const char *s2, size_t n);
extern int strcoll(const char *str1, const char *str2);
extern char *strcpy(char *toHere, const char *fromHere);
extern char *strncpy(char *s1, const char *s2, size_t n);
extern const char *strerror(int errnum);
extern size_t strlen(const char *s);
extern size_t strspn(const char *s1, const char *s2);
extern size_t strcspn(const char *s1, const char *s2);
extern char *strpbrk(const char *s1, const char *s2);
extern char *strstr(const char *haystack, const char *needle);
extern char *strtok_r(char *s, const char *delimiters, char **lasts);
extern char *strtok(char *s1, const char *delimiters);
extern size_t strxfrm(char *dest, const char *src, size_t n);

#endif
