#include <lib.h>

#include <bach/module.h>
#include <bach/serial.h>
#include <bach/irq.h>
#include <bach/jiffies.h>
#include <bach/types.h>
#include <bach/task.h>
#include <bach/system.h>
#include <bach/alloc.h>

#include <asm/memory.h>

extern initcall_t __initcall_begin, __initcall_end;
extern exitcall_t __exitcall_begin, __exitcall_end;
extern u32 __alloc_begin;

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
	/* Deinitialize in reverse */
	call = &__exitcall_end;
	call--;
	do {
		(*call)();
		call--;
	} while (call >= &__exitcall_begin);
}

void * task1(void *val)
{
	kputs("S");
	return val;
}

void * task2(void *val)
{
	kputs("T");
	return val;
}

static struct bach_task_attr task_list[] = {
	{
		.name = "second",
		.period = 1000,
		.job = task1,
		.arg = 0,
		.initial = 0
	},
	{
		.name = "tensec",
		.period = 10000,
		.job = task2,
		.arg = 0,
		.initial = 0
	}
};

int kernel_main(void)
{
	u32 i;

	mem_setup();
	irq_setup();
	init_tasks();
	init_alloc((u32)&__alloc_begin, HEAP_SIZE);

	do_initcalls();

	for(i = 0; i < ARRAY_SIZE(task_list); i++)
		task_register(task_list + i);

	irq_enable();

	kernel_mainloop();

	do_exitcalls();

	for(;;);
	return 0;
}
