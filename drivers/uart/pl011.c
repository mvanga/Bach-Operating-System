#include <bach/module.h>
#include <bach/types.h>
#include <bach/serial.h>

u32 __serial_base = 0x101F1000;
#define SERIAL_BASE ((volatile u32 *)__serial_base)

#define FLAG_BUSY (1 << 3)

enum serial_regs {
	SERIAL_DATA,
	SERIAL_RX_STATUS,
	SERIAL_08_RESERVED,
	SERIAL_0C_RESERVED,
	SERIAL_10_RESERVED,
	SERIAL_14_RESERVED,
	SERIAL_FLAGS,
	SERIAL_1C_RESERVED
};

static void putc (char c)
{
	volatile u32 *base = SERIAL_BASE;
	/* Serial console wants /n/r */
	if (c == '\n')
		putc('\r');
	/* Wait till serial line is idle */
	while (base[SERIAL_FLAGS] & FLAG_BUSY);
	base[SERIAL_DATA] = c;
}

static void puts (const char *str)
{
	while(*str != '\0')
		putc(*str++);
}

int pl011_init(void)
{
	register_uart(&putc, &puts);
	kputs("PL011 serial driver initialized\n");
	return 0;
}

void pl011_exit(void)
{
	kputs("PL011 serial driver exited\n");
}

driver_init(pl011_init);
driver_exit(pl011_exit);
