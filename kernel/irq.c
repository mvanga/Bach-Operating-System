#include <bach/irq.h>
#include <bach/types.h>
#include <bach/serial.h>
#include <bach/jiffies.h>

struct irq_handler {
	irq_handler_t handler;
	void *arg;
	u32 count;
};

struct irq_handler handlers[MAX_IRQ_HANDLERS];

u32 bach_irq_stack[IRQ_STACKSIZE];

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

void irq_setup(void)
{
	int i;
	for (i = 0; i < MAX_IRQ_HANDLERS; i++) {
		handlers[i].handler = 0;
		handlers[i].arg = 0;
		handlers[i].count = 0;
	}
}

void bach_irq_handler(void)
{
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
