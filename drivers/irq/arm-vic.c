#include <bach/irq.h>
#include <bach/types.h>
#include <bach/serial.h>
#include <bach/jiffies.h>

#define VIC_BASE 0x10140000
#define VIC ((volatile u32 *)VIC_BASE)

enum vic_registers {
	/* 0x00 */
	VIC_STATUS,
	VIC_FIQSTATUS,
	VIC_RAWPENDING,
	VIC_SELECT,
	/* 0x10 */
	VIC_ENABLE,
	VIC_DISABLE
};

int irq_getnr(void)
{
	int i, j = 0;

	i = VIC[VIC_STATUS];

	while (! (i & 1)) {
		i >>= 1;
		j++;
	}
	return j;
}

void irq_mask(int irq)
{
	VIC[VIC_DISABLE] = 1 << irq;
}

void irq_unmask(int irq)
{
	VIC[VIC_ENABLE] = 1 << irq;
}
