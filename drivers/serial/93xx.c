#include <bach/module.h>
#include <bach/serial.h>
#include <bach/types.h>

#define SER_DATA	((volatile u32 *)0x808c0000)
#define SER_FLAGS	((volatile u32 *)0x808c0018)
#define BIT_BUSY	0x08

static void putc(char c)
{
	/* serial wants \r\n */
	if (c == '\n')
		putc('\r');

	/* wait for the serial to be idle (no transmission) */
	while (*SER_FLAGS & BIT_BUSY);

	*SER_DATA = c;
}

int init_93xx(void)
{
	register_uart_driver(&putc);
	kputs("Serial (93xx) driver initialized\n");
	return 0;
}

void exit_93xx(void)
{
	kputs("Serial (93xx) driver exited\n");
}

driver_init(init_93xx);
driver_exit(exit_93xx);
