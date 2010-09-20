#include <klib_glue.h>

void _glue_exit(int ret)
{
	ret = 0;
	for(;;);
}
