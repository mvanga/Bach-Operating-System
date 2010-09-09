#include <bach/module.h>
#include <bach/irq.h>
#include <bach/types.h>
#include <bach/jiffies.h>
#include <bach/serial.h>

#define TIMER   ((volatile u32 *)0x101e3000)

u32 timer_nr;

void timer_irq_handler(void *arg)
{
	u32 nr = *(u32*)arg;
	nr = 0;
	TIMER[3] = 0;
}

int timer_init(void)
{
	/* The timer is fed by 1MHz */
	TIMER[0] = (1000000 + (HZ / 2)) / HZ;   /* load register */
	TIMER[6] = (1000000 + (HZ / 2)) / HZ;   /* background load register */
	TIMER[2] = 0xe2;            /* periodic, enable */
	if (irq_request(5, &timer_irq_handler, (void *)&timer_nr) == -1) {
		kputs("Timer (SP804) driver initalization failed\n");
		return -1;
	}
	kputs("Timer (SP804) driver initialized\n");
	return 0;
}

void timer_exit(void)
{
	irq_free(5, (void *)&timer_nr);
	kputs("Timer (SP804) driver exited\n");
}

driver_init(timer_init);
driver_exit(timer_exit);
