include config/env.mk
include .config

# Main kernel source files
obj-y += kernel/main.o kernel/serial.o kernel/irq.o kernel/time.o kernel/task.o kernel/alloc.o
# Architecture specific source files
obj-$(ARCH_ARM) += arch/arm/boot.o arch/arm/vectors.o arch/arm/irq.o arch/arm/memory.o
# Kernel library files
obj-y += klib/string.o klib/_divsi3.o  klib/_udivsi3.o klib/div0.o
# Kernel space standard C library
cflags-$(CONFIG_KLIBC) += -I./lib/include
obj-$(CONFIG_KLIBC) += lib/string/memchr.o lib/string/memcmp.o lib/string/memmove.o \
				lib/string/memset.o lib/string/strcat.o lib/string/strchr.o \
				lib/string/strcmp.o lib/string/strcoll.o lib/string/strcpy.o \
				lib/string/strcspn.o lib/string/strerror.o lib/string/strlen.o \
				lib/string/strncmp.o lib/string/strncpy.o lib/string/strpbrk.o \
				lib/string/strrchr.o lib/string/strspn.o lib/string/strstr.o \
				lib/string/strtok.o lib/string/strxfrm.o lib/string/memcpy.o \
				\
				lib/assert/assert_fail.o \
				\
				lib/ctype/isalnum.o lib/ctype/isalpha.o lib/ctype/isblank.o \
				lib/ctype/iscntrl.o lib/ctype/isdigit.o lib/ctype/isgraph.o \
				lib/ctype/islower.o lib/ctype/isprint.o lib/ctype/ispunct.o \
				lib/ctype/isspace.o lib/ctype/isupper.o lib/ctype/isxdigit.o \
				lib/ctype/tolower.o lib/ctype/toupper.o \
				\
				lib/errno/errno_location.o \
				\
				lib/stdlib/getenv.o lib/stdlib/putenv.o lib/stdlib/environ.o \
				lib/stdlib/strtod.o lib/stdlib/strtol.o lib/stdlib/strtoll.o \
				lib/stdlib/strtoul.o lib/stdlib/strtoull.o lib/stdlib/atexit.o \
				lib/stdlib/atoi.o lib/stdlib/atol.o lib/stdlib/atof.o \
				lib/stdlib/rand.o lib/stdlib/rand_r.o lib/stdlib/rand48.o \
				lib/stdlib/qsort.o lib/stdlib/bsearch.o lib/stdlib/div.o \
				lib/stdlib/ldiv.o \
				\
				lib/malloc/calloc.o lib/malloc/free.o lib/malloc/malloc.o \
				lib/malloc/malloc_memobj.o lib/malloc/memalign.o lib/malloc/realloc.o \
				\
				lib/klib_glue.o

# Driver files
obj-$(CONFIG_ARM_VIC) += drivers/irq/arm-vic.o

obj-$(CONFIG_UART_93XX) += drivers/serial/93xx.o
obj-$(CONFIG_UART_PL011) += drivers/serial/pl011.o

obj-$(CONFIG_TIMER_SP804) += drivers/timer/sp804.o

include config/build.mk
