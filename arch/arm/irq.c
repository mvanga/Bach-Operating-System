#include <asm/irq.h>

#include <bach/types.h>

#include <bach/irq.h>

void irq_enable(void)
{
	u32 i;
	asm volatile("mrs %0, cpsr\n\t"
				 "bic %0, %0, #0xc0\n\t"
				 "msr cpsr_c, %0\n"
				 : "=r" (i) );
	fiq_disable();
}

void irq_disable(void)
{
	u32 i;
	asm volatile("mrs %0, cpsr\n\t"
				 "orr %0, %0, #0xc0\n\t"
				 "msr cpsr_c, %0\n"
				 : "=r" (i) );
}

void fiq_disable(void)
{
	u32 i;
	asm volatile("mrs %0, cpsr\n\t"
				 "orr %0, %0, #0x40\n\t"
				 "msr cpsr_c, %0\n"
				 : "=r" (i) );
}
