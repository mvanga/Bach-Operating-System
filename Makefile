# Cross compilation toolchain
AS=$(CROSS_COMPILE)as
CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld
# Compilation flags
ASFLAGS=
CFLAGS=-Wall -ggdb -Wextra -nostdlib -nostartfiles -ffreestanding -std=gnu99 -I./include

# Kernel specific stuff
NAME=bach
LINKER_FILE=$(NAME).lds
KERNEL_MAJOR=0
KERNEL_MINOR=01
KERNEL_NAME=$(NAME)-$(KERNEL_MAJOR).$(KERNEL_MINOR)

# The main kernel source files
obj-y = boot.o vectors.o main.o serial.o memory.o



# Build Rules

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
