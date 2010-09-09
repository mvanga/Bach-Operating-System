#ifndef BACH_TASK_H
#define BACH_TASK_H

#include <bach/types.h>

#include <asm/task.h>

#define MAX_TASKS	10

#define RUNNING	0
#define BLOCKED 1
#define KILLED  2

#define for_each_task(t, i) \
    for (i = 0, t = tasks; \
		 i < MAX_TASKS; \
		 i++, t++)

typedef void * (*bach_job)(void *arg);

struct bach_task_attr {
	bach_job job;
	void *arg;
	s32 priority;
	char *name;
	u32 stack_size;
	u32 period;
	u32 initial;
};

struct bach_task {
	const struct bach_task_arch *arch;
	const struct bach_task_attr *attr;
	u32 nextrun;
	u32 period;
	u32 *stack;
	int state;
	void *arg;
};

extern struct bach_task tasks[MAX_TASKS];

int task_register(const struct bach_task_attr *attr);
int task_unregister(int idx);
void init_tasks();
void kernel_mainloop(void);

#endif