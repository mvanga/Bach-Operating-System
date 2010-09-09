#include <bach/serial.h>

struct serial_driver uart = { .putc = 0 };

void kputc(char c)
{
	if (uart.putc)
		uart.putc(c);
}

void kputs(const char *str)
{
	while (*str) {
		if (uart.putc)
			uart.putc(*str++);
	}
}

void register_uart(putc_f putc)
{
	uart.putc = putc;
}
