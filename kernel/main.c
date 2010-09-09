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
	call = &__exitcall_end;
	call--;
	do {
		(*call)();
		call--;
	} while (call >= &__exitcall_begin);
}

int kernel_main(void)
{
	mem_setup();
	irq_setup();

	do_initcalls();

	irq_enable();

	kputs("Hello World\n");
	for(;;);

	do_exitcalls();

	return 0;
}
