#ifndef BACH_SERIAL_H
#define BACH_SERIAL_H

typedef void (*putc_f)(char);
typedef void (*puts_f)(const char *);

struct serial_driver {
	putc_f putc;
	puts_f puts;
} uart;

void kputc(char c);
void kputs(const char *str);
void register_uart(putc_f putc, puts_f puts);

#endif
