#ifndef BACH_IRQ_H
#define BACH_IRQ_H

#define BACH_IRQ_STACKSIZE	128

#ifndef __ASSEMBLY__

/* Device specific functions */
extern int irq_getnr(void);
extern void irq_mask(int irq);
extern void irq_unmask(int irq);

/* Device independent functions */
void bach_irq_enable(void);
void bach_irq_setup(void);
#endif

#endif
