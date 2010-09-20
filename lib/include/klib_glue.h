#ifndef __KLIB_GLUE_H__
#define __KLIB_GLUE_H__

#include <stddef.h>

void _glue_exit(int ret) __attribute__((weak));
void _glue_free(void *ptr) __attribute__((weak));
void *_glue_alloc(size_t size) __attribute__((weak));
void *_glue_alloc_align(size_t size, size_t align) __attribute__((weak));
void *_glue_realloc(void *ptr, size_t new_size) __attribute__((weak));

#endif
