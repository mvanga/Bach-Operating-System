#ifndef BACH_ARCH_ARM_TASK_H
#define BACH_ARCH_ARM_TASK_H

#include <bach/task.h>

register struct bach_task *current asm ("r8");

struct bach_task_arch {
	int test;
};

#endif
