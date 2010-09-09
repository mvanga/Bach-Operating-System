#include <bach/types.h>
#include <bach/system.h>

#define ZERO ((u32 *)0)

void mem_setup(void)
{
	int i;
	for (i = 0; i < 16; i++)
		ZERO[i] = vectors[i];
}
