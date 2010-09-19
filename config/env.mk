# Cross compilation toolchain
AS=$(CROSS_COMPILE)as
CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)gcc
OBJCOPY=$(CROSS_COMPILE)objcopy

ARCH?=arm
ifeq ($(ARCH),arm)
ARCH_ARM=y
endif

# Compilation flags
ASFLAGS=-I./include -I./arch/$(ARCH)/include -D__ASSEMBLY__
CFLAGS=-Wall -ggdb -Wextra -nostdlib -nostartfiles -ffreestanding -std=gnu99 -I./include -I./arch/$(ARCH)/include

# Kernel specific stuff
NAME=bach
LINKER_FILE=$(NAME).lds

ELF=$(NAME)
BIN=$(NAME).bin
SREC=$(NAME).srec
