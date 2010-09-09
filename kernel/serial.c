#include <bach/serial.h>

struct serial_driver uart = { .putc = 0, .puts = 0 };

void kputc(char c)
{
	if (uart.putc)
		uart.putc(c);
}

void kputs(const char *str)
{
	if (uart.puts)
		uart.puts(str);
}

void register_uart(putc_f putc, puts_f puts)
{
	uart.putc = putc;
	uart.puts = puts;
}
