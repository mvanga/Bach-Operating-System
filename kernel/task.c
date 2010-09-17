#include <bach/task.h>
#include <bach/jiffies.h>
#include <bach/system.h>

struct bach_task tasks[MAX_TASKS];
static int num_tasks = 0;

int next_task_index(void)
{
	int i;
	struct bach_task *t;
	for_each_task(t, i) {
		if (t->state == TASK_STOPPED)
			return i;
	}
	return -1;
}

int task_register(const struct bach_task_attr *attr)
{
	struct bach_task *t;
	if (num_tasks >= MAX_TASKS)
		return -1;
	
	int task_idx = next_task_index();
	if (task_idx == -1)
		return -1;
	t = &tasks[task_idx];
	t->attr = attr;
	t->nextrun = msecs_to_jiffies(attr->initial);
	t->period = msecs_to_jiffies(attr->period);
	t->state = TASK_RUNNING;
	t->arg = attr->arg;
	t->custom_blk = NULL;
	num_tasks++;
	return task_idx;
}

int task_unregister(int idx)
{
	struct bach_task *t;
	if (idx >= MAX_TASKS)
		return -1;
	t = &tasks[idx];
	if (t->state == TASK_STOPPED)
		return -1;

	t->state = TASK_STOPPED;
	num_tasks--;
	return 0;
}

void init_tasks()
{
	int i;
	struct bach_task *t;
	for_each_task(t, i) {
		t->state = TASK_STOPPED;
	}
}

void kernel_mainloop(void)
{
	u32 j;
	int i;
	struct bach_task *t;

	/* Loop forever if we have no tasks */
	while(num_tasks == 0);

	j = jiffies + 2;
	for_each_task(t, i) {
		t->nextrun += j;
	}

	while(1) {
		current = 0;
		for_each_task(t, i) {
			if (t->state == TASK_STOPPED)
				continue;
			if (!current) {
				current = t;
				continue;
			}
			if (time_before(t->nextrun, current->nextrun)) {
				current = t;
				continue;
			}
			if (t->nextrun == current->nextrun) {
				if (t->attr->priority > current->attr->priority)
					current = t;
			}
		}

		while(time_before(jiffies, current->nextrun));
		current->attr->job(current->arg);
		current->nextrun += current->period;
	}
}
