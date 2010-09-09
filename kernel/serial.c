#include <bach/serial.h>
#include <bach/stdarg.h>
#include <bach/string.h>

struct serial_driver uart = { .putc = 0 };

void kitoa(char *buf, unsigned long int n, int base)
{
	unsigned long int tmp;
	int i, j;
	tmp = n;
	i = 0;
	do {
		tmp = n % base;
		buf[i++] = (tmp < 10) ? (tmp + '0') : (tmp + 'A' - 10);
	} while (n /= base);
	buf[i--] = 0;

	for (j = 0; j < i; j++, i--) {
		tmp = buf[j];
		buf[j] = buf[i];
		buf[i] = tmp;
	}
}

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

void kputhex(u32 n)
{
	s32 tmp;
	kputs("0x");
	char zeroes = 1;
	int i;
	for (i = 28; i > 0; i -= 4) {
		tmp = (n >> i) & 0xF;
		if (tmp == 0 && zeroes != 0)
			continue;
		if (tmp >= 0xA) {
			zeroes = 0;
			kputc(tmp - 0xA + 'a' );
		} else {
			zeroes = 0;
			kputc( tmp+'0' );
		}
	}
	tmp = n & 0xF;

	if (tmp >= 0xA)
		kputc (tmp - 0xA + 'a');
	else
		kputc (tmp+'0');
}

void kputdec(u32 n)
{

	if (n == 0) {
		kputc('0');
		return;
	}
	s32 acc = n;
	char c[32];
	int i = 0;
	while (acc > 0) {
		c[i] = '0' + acc%10;
		acc /= 10;
		i++;
	}
	c[i] = 0;

	char c2[32];
	c2[i--] = 0;
	int j = 0;
	while(i >= 0)
		c2[i--] = c[j++];
	kputs(c2);
}

void printk(char *s, ...)
{
	va_list ap;
	
	char buf[16];
	int i, j, size, buflen, neg;
	
	unsigned char c;
	int ival;
	unsigned int uival;
	
	va_start(ap, s);
	
	while ((c = *s++)) {
		size = 0;
		neg = 0;
		
		if (c == 0) {
			break;
		} else if (c == '%') {
			c = *s++;
			if (c >= '0' && c <= '9') {
				size = c - '0';
				c = *s++;
			}
			
			if (c == 'd') {
				ival = va_arg(ap, int);
				if (ival < 0) {
					uival = 0 - ival;
					neg++;
				} else {
					uival = ival;
				}
				kitoa(buf, uival, 10);
				
				buflen = kstrlen(buf);
				if (buflen < size)
					for (i = size, j = buflen; i >= 0; i--, j--)
						buf[i] = (j >= 0) ? buf[j] : '0';
					
				if (neg)
					printk("-%s", buf);
				else
					printk(buf);
			} else if (c == 'u') {
				uival = va_arg(ap, int);
				kitoa(buf, uival, 10);
			
				buflen = kstrlen(buf);
				if (buflen < size)
					for (i = size, j = buflen; i >= 0; i--, j--)
						buf[i] = (j >= 0) ? buf[j] : '0';

				printk(buf);
			} else if (c == 'x' || c == 'X') {
				uival = va_arg(ap, int);
				kitoa(buf, uival, 16);

				buflen = kstrlen(buf);
				if (buflen < size)
					for (i = size, j = buflen; i >= 0; i--, j--)
						buf[i] = (j >= 0) ? buf[j] : '0';

				printk("0x%s", buf);
			} else if (c == 'p') {
				uival = va_arg(ap, int);
				kitoa(buf, uival, 16);
				size = 8;

				buflen = kstrlen(buf);
				if (buflen < size)
					for (i = size, j = buflen; i >= 0; i--, j--)
						buf[i] = (j >= 0) ? buf[j] : '0';

				printk("0x%s", buf);
			} else if (c == 's') {
				printk((char *) va_arg(ap, int));
			} else if (c == 'c') {
				u8 cval = va_arg(ap, int);
				kputc(cval);
			}
		} else {
			kputc(c);
		}
	}
	
	return;
}

void register_serial_driver(putc_f putc)
{
	uart.putc = putc;
}
