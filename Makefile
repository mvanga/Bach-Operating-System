include config/config.mk

# Cross compilation toolchain
AS=$(CROSS_COMPILE)as
CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld
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

# Architecture specific source files
obj-$(ARCH_ARM) += arch/arm/boot.o arch/arm/vectors.o arch/arm/irq.o arch/arm/memory.o
# Main kernel source files
obj-y += kernel/main.o kernel/serial.o kernel/irq.o kernel/time.o kernel/task.o kernel/alloc.o
# Kernel library files
obj-y += klib/string.o klib/_divsi3.o  klib/_udivsi3.o klib/div0.o

# Driver files
obj-$(CONFIG_ARM_VIC) += drivers/irq/arm-vic.o

obj-$(CONFIG_UART_93XX) += drivers/serial/93xx.o
obj-$(CONFIG_UART_PL011) += drivers/serial/pl011.o

obj-$(CONFIG_TIMER_SP804) += drivers/timer/sp804.o

# Build Rules

all: force $(ELF) $(BIN) $(SREC)

$(ELF): $(obj-y)
	$(LD) -T $(LINKER_FILE) $(LDFLAGS) $(obj-y) -o $@

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $^ $@

$(SREC): $(ELF)
	$(OBJCOPY) -O srec $^ $@

clean:
	rm -rf $(obj-y) $(ELF) $(BIN) $(SREC)

run:
	qemu-system-arm -M versatilepb -m 128 -kernel $(ELF) -serial stdio

force:
