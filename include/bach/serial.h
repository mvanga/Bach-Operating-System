#ifndef BACH_SERIAL_H
#define BACH_SERIAL_H

#include <bach/types.h>

typedef void (*putc_f)(char);

struct serial_driver {
	putc_f putc;
};

void kputc(char c);
void kputs(const char *str);
void kputhex(u32 n);
void kputdec(u32 n);
void printk(char *s, ...);

void register_uart_driver(putc_f putc);

#endif
