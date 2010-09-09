#ifndef BACH_ALLOC_H
#define BACH_ALLOC_H

#include <bach/types.h>

#define HEAP_SIZE 1000

void init_alloc(u32 start, u32 size);

void *kmalloc(u32 size);
void kfree(void *ptr);

void print_blocks();

#endif
