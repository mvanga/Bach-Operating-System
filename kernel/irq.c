#include <bach/irq.h>
#include <bach/types.h>
#include <bach/serial.h>
#include <bach/jiffies.h>

#define TIMER   ((volatile u32 *)0x101e3000)

struct irq_handler {
	irq_handler_t handler;
	void *arg;
	u32 count;
};

struct irq_handler handlers[MAX_IRQ_HANDLERS];

u32 bach_irq_stack[BACH_IRQ_STACKSIZE];

int irq_request(int irq, irq_handler_t handler, void *arg)
{
	if (handlers[irq].handler)
		return -1;
	handlers[irq].handler = handler;
	handlers[irq].arg = arg;
	handlers[irq].count = 0;
	irq_unmask(irq);
	return 0;
}

int irq_free(int irq, void *arg)
{
	if (! handlers[irq].handler)
		return -1;
	if (arg != handlers[irq].arg)
		return -1;
	handlers[irq].handler = 0;
	handlers[irq].arg = 0;
	handlers[irq].count = 0;
	irq_mask(irq);
	return 0;
}

void irq_enable(void)
{
	    u32 i;
		asm volatile("mrs %0, cpsr\n\t"
					 "bic %0, %0, #0xc0\n\t"
					 "msr cpsr_c, %0\n"
					 : "=r" (i) );
}

void irq_setup(void)
{
	int i;
	for (i = 0; i < MAX_IRQ_HANDLERS; i++) {
		handlers[i].handler = 0;
		handlers[i].arg = 0;
		handlers[i].count = 0;
	}
	/* The timer is fed by 1MHz */
//	TIMER[0] = (1000000 + (HZ / 2)) / HZ;   /* load register */
//	TIMER[6] = (1000000 + (HZ / 2)) / HZ;   /* background load register */
//	TIMER[2] = 0xe2;            /* periodic, enable */
//	irq_unmask(5);              /* enable interrupt 5 */
}

void bach_irq_handler(void)
{
//	TIMER[3] = 0;
	u32 nr = irq_getnr();
	if (nr >= MAX_IRQ_HANDLERS)
		return;
	if (handlers[nr].handler) {
		handlers[nr].handler(handlers[nr].arg);
		return;
	}
	irq_mask(nr);
	kputs("Disabled unknown interrupt\n");
}
