#include <bach/serial.h>
#include <bach/memory.h>

int kernel_main(void)
{
	bach_mem_setup();

	puts("Hello World\n");

	return 0;
}
