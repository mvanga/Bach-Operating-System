#ifndef BACH_IRQ_H
#define BACH_IRQ_H

#define BACH_IRQ_STACKSIZE	128
#define MAX_IRQ_HANDLERS 32

#ifndef __ASSEMBLY__

typedef void (*irq_handler_t)(void *);

/* Device specific functions */
extern int irq_getnr(void);
extern void irq_mask(int irq);
extern void irq_unmask(int irq);

/* Device independent functions */


int irq_request(int irq, irq_handler_t handler, void *arg);
int irq_free(int irq, void *arg);
void irq_enable(void);
void irq_setup(void);
#endif

#endif
