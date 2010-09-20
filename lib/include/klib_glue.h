#ifndef __KLIB_GLUE_H__
#define __KLIB_GLUE_H__

#include <stddef.h>

#define PAGE_SIZE 4096

#define MREMAP_MAYMOVE  1UL
#define MREMAP_FIXED    2UL

#define PROT_READ   0x1
#define PROT_WRITE  0x2
#define PROT_EXEC   0x4
#define PROT_NONE   0x0

#define MAP_SHARED  0x01
#define MAP_PRIVATE 0x02

#if defined (__arm__)
#define MAP_FIXED   0x10        /* Interpret addr exactly */
#define MAP_ANONYMOUS   0x20        /* don't use a file */
#define MAP_GROWSDOWN   0x0100      /* stack-like segment */
#define MAP_DENYWRITE   0x0800      /* ETXTBSY */
#define MAP_EXECUTABLE  0x1000      /* mark it as an executable */
#define MAP_LOCKED  0x2000      /* pages are locked */
#define MAP_NORESERVE   0x4000      /* don't check for reservations */
#define MAP_POPULATE    0x8000
#define MS_ASYNC    1       /* sync memory asynchronously */
#define MS_INVALIDATE   2       /* invalidate the caches */
#define MS_SYNC     4       /* synchronous memory sync */
#define MCL_CURRENT 1       /* lock all current mappings */
#define MCL_FUTURE  2       /* lock all future mappings */
#define MADV_NORMAL 0x0     /* default page-in behavior */
#define MADV_RANDOM 0x1     /* page-in minimum required */
#define MADV_SEQUENTIAL 0x2     /* read-ahead aggressively */
#define MADV_WILLNEED   0x3     /* pre-fault pages */
#define MADV_DONTNEED   0x4     /* discard these pages */
#endif

void _glue_exit(int ret) __attribute__((weak));

void *mmap(void *__addr, size_t __len, int __prot,
                   int __flags, int __fd, off_t __offset) __attribute__((weak));
int munmap(void *__addr, size_t __len) __attribute__((weak));
void *mremap(void *__addr, size_t __old_len, size_t __new_len,
             unsigned long __may_move) __attribute__((weak));

#endif
