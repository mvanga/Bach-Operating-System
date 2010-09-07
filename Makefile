# Cross compilation toolchain
AS=$(CROSS_COMPILE)as
CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld
# Compilation flags
ASFLAGS=
CFLAGS=-Wall -ggdb -Wextra -nostdlib -nostartfiles -ffreestanding -std=gnu99 -I./include

NAME=bach
LINKER_FILE=$(NAME).lds
KERNEL_NAME=$(NAME)

obj-y = boot.o vectors.o main.o serial.o

all: $(KERNEL_NAME)

$(KERNEL_NAME): $(obj-y)
	$(LD) -T $(LINKER_FILE) -o $(KERNEL_NAME) $(obj-y)

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(obj-y) $(KERNEL_NAME)

run:
	qemu-system-arm -M versatilepb -m 128 -kernel $(KERNEL_NAME) -serial stdio
