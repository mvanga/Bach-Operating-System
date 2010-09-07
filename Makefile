AS=$(CROSS_COMPILE)as
CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld

SOURCES=boot.o vectors.o main.o serial.o

ASFLAGS=
CFLAGS=-Wall -ggdb -Wextra -nostdlib -nostartfiles -ffreestanding -std=gnu99 -I./include

LINKER_FILE=link.ld
KERNEL_NAME=kernel

all: $(KERNEL_NAME)

$(KERNEL_NAME): $(SOURCES)
	$(LD) -T $(LINKER_FILE) -o $(KERNEL_NAME) $(SOURCES)

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(SOURCES) $(KERNEL_NAME)

run:
	qemu-system-arm -M versatilepb -m 128 -kernel $(KERNEL_NAME) -serial stdio
