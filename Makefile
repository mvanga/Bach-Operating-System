include config/env.mk
include .config

# Main kernel source files
obj-y += kernel/main.o kernel/serial.o kernel/irq.o kernel/time.o kernel/task.o kernel/alloc.o
# Architecture specific source files
obj-$(ARCH_ARM) += arch/arm/boot.o arch/arm/vectors.o arch/arm/irq.o arch/arm/memory.o
# Kernel library files
obj-y += klib/string.o klib/_divsi3.o  klib/_udivsi3.o klib/div0.o

# Driver files
obj-$(CONFIG_ARM_VIC) += drivers/irq/arm-vic.o

obj-$(CONFIG_UART_93XX) += drivers/serial/93xx.o
obj-$(CONFIG_UART_PL011) += drivers/serial/pl011.o

obj-$(CONFIG_TIMER_SP804) += drivers/timer/sp804.o

include config/build.mk
