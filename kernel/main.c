#include <bach/module.h>
#include <bach/serial.h>
#include <bach/memory.h>
#include <bach/irq.h>

extern initcall_t __initcall_begin, __initcall_end;
extern exitcall_t __exitcall_begin, __exitcall_end;

void do_initcalls(void)
{
	initcall_t *call;
	call = &__initcall_begin;
	do {
		(*call)();
		call++;
	} while (call < &__initcall_end);
}

void do_exitcalls(void)
{
	exitcall_t *call;
	call = &__exitcall_begin;
	do {
		(*call)();
		call++;
	} while (call < &__exitcall_end);
}

int kernel_main(void)
{
	bach_mem_setup();

	do_initcalls();

	bach_irq_setup();
	bach_irq_enable();

	kputs("Hello World\n");

	do_exitcalls();

	for(;;);
	return 0;
}
