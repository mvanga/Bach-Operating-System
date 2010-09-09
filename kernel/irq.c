#include <bach/irq.h>
#include <bach/types.h>
#include <bach/serial.h>
#include <bach/jiffies.h>

#define TIMER   ((volatile u32 *)0x101e3000)

u32 bach_irq_stack[BACH_IRQ_STACKSIZE];

void bach_irq_enable(void)
{
	    u32 i;
		asm volatile("mrs %0, cpsr\n\t"
					 "bic %0, %0, #0xc0\n\t"
					 "msr cpsr_c, %0\n"
					 : "=r" (i) );
}

void bach_irq_setup(void)
{
	/* The timer is fed by 1MHz */
	TIMER[0] = (1000000 + (HZ / 2)) / HZ;   /* load register */
	TIMER[6] = (1000000 + (HZ / 2)) / HZ;   /* background load register */
	TIMER[2] = 0xe2;            /* periodic, enable */
	irq_unmask(5);              /* enable interrupt 5 */
}

void bach_irq_handler(void)
{
	TIMER[3] = 0;
}
