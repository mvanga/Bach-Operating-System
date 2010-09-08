# Cross compilation toolchain
AS=$(CROSS_COMPILE)as
CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld
OBJCOPY=$(CROSS_COMPILE)objcopy
# Compilation flags
ASFLAGS=
CFLAGS=-Wall -ggdb -Wextra -nostdlib -nostartfiles -ffreestanding -std=gnu99 -I./include

# Kernel specific stuff
NAME=bach
LINKER_FILE=$(NAME).lds
KERNEL_MAJOR=0
KERNEL_MINOR=01

ELF=$(NAME)-$(KERNEL_MAJOR).$(KERNEL_MINOR)
BIN=$(NAME)-$(KERNEL_MAJOR).$(KERNEL_MINOR).bin
SREC=$(NAME)-$(KERNEL_MAJOR).$(KERNEL_MINOR).srec

# The main kernel source files
obj-y = boot.o vectors.o main.o serial.o memory.o



# Build Rules

all: $(ELF) $(BIN) $(SREC)

$(ELF): $(obj-y)
	$(LD) -T $(LINKER_FILE) $(obj-y) -o $@

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $^ $@

$(SREC): $(ELF)
	$(OBJCOPY) -O srec $^ $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(obj-y) $(ELF) $(BIN) $(SREC)

run:
	qemu-system-arm -M versatilepb -m 128 -kernel $(ELF) -serial stdio -nographic
