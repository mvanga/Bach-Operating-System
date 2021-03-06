include .config
include .config_defs

option_defs=$(patsubst %,-D%, $(opt-y))

# Cross compilation toolchain
AS=$(CROSS_COMPILE)as
CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld
OBJCOPY=$(CROSS_COMPILE)objcopy

ARCH?=arm
ifeq ($(ARCH),arm)
ARCH_ARM=y
ARCH_FLAG=__arm__
endif

# Compilation flags
ASFLAGS=-I./include -I./arch/$(ARCH)/include -D__ASSEMBLY__ $(option_defs)
CFLAGS=-Wall -ggdb -Wextra -nostdlib -nostartfiles -ffreestanding -std=gnu99 -I./include -I./arch/$(ARCH)/include $(option_defs)
LDFLAGS=-nostartfiles /opt/eldk-4.2/usr/lib/gcc/arm-linux-gnueabi/4.2.2/libgcc.a

# Kernel specific stuff
NAME=bach
LINKER_FILE=$(NAME).lds

ELF=$(NAME)
BIN=$(NAME).bin
SREC=$(NAME).srec
