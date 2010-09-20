#ifndef __KLIB_STDDEF_H__
#define __KLIB_STDDEF_H__

#ifdef __GNUC__
typedef __PTRDIFF_TYPE__ ptrdiff_t;
typedef __SIZE_TYPE__ size_t;
#if !defined(__cplusplus)
typedef __WCHAR_TYPE__ wchar_t;
#endif
#else
typedef signed long ptrdiff_t;
typedef unsigned long size_t;
typedef int wchar_t;
#endif

typedef signed long ssize_t;

#undef NULL
#if defined(__cplusplus)
#define NULL 0
#else
#define NULL ((void *)0)
#endif

enum {
	false	= 0,
	true	= 1
};

#undef offsetof
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#endif
