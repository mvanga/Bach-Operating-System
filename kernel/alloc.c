#include <bach/alloc.h>
#include <bach/types.h>
#include <bach/serial.h>
#include <bach/system.h>

#define MAGIC_CHECK 0xDEEEDAAA

#define for_each_block(t, i) \
	for(t = head, i = 0; \
		t != NULL; \
		t=t->next, i++)

struct header *head;
u32 current;

struct header {
	u32 magic;
	u32 size;
	void *mem;
	int used;
	struct footer *foot;
	struct header *next;
	struct header *prev;
};

struct footer {
	u32 magic;
	struct header *head;
};

u32 simple_malloc(u32 size)
{
	u32 ret = current;
	current += size;
	return ret;
}

void init_alloc(u32 start, u32 size)
{
	current = start;
	u32 msize = size - sizeof(struct header) - sizeof(struct footer);

	head = (struct header *)simple_malloc(sizeof(struct header));
	head->magic = MAGIC_CHECK;
	head->size = msize;
	head->mem = (void *)simple_malloc(msize);
	head->next = NULL;
	head->prev = NULL;
	head->used = 0;

	struct footer *foot = (struct footer *)simple_malloc(sizeof(struct footer));
	foot->magic = MAGIC_CHECK;
	foot->head = head;

	head->foot = foot;
}

void break_block(struct header *block, u32 size)
{
	struct footer *new_foot = (struct footer *)((u32)block->mem + size);
	struct header *new_head = (struct header *)((u32)new_foot + sizeof(struct footer));
	new_head->magic = MAGIC_CHECK;
	new_head->size = block->size - size - sizeof(struct header) - sizeof(struct footer);
	new_head->mem = (void *)((u32)new_head + sizeof(struct header));
	new_head->foot = block->foot;
	new_head->prev = block;
	new_head->next = block->next;
	new_head->used = 0;

	new_foot->head = block;
	
	block->size = size;
	block->foot->head = new_head;
	block->next->prev = new_head;
	block->foot = new_foot;
	block->next = new_head;
}

void merge_next(struct header *block)
{
	struct header *right = block->next;
	/* TODO: check for magic flag here */
	block->foot = right->foot;
	right->foot->head = block;
	right->next->prev = block;
	block->next = right->next;
	block->size += sizeof(struct header) + sizeof(struct footer) + right->size;
}

void merge_prev(struct header *block)
{
	struct header *left = block->prev;
	struct header *right = block->next;
	/* TODO: check for magic flag here */
	left->next = right;
	right->prev = left;
	left->foot = block->foot;
	block->foot->head = left;
	left->size += sizeof(struct header) + sizeof(struct footer) + block->size;
}

void *kmalloc(u32 size)
{
	int i;
	struct header *t;
	struct header *fit = NULL;
	for_each_block(t, i) {
		if (t->used)
			continue;
		if (fit == NULL) {
			fit = t;
			continue;
		}
		if (t->size >= size && t->size < fit->size) {
			fit = t;
			continue;
		}
	}
	if (fit == NULL)
		return NULL;
	/* Check if we can break the block down */
	int left = fit->size - size - sizeof(struct header) - sizeof(struct footer);
	if (left > 4)
		break_block(fit, size);
	fit->used = 1;
	print_blocks();
	return fit->mem;
}

void kfree(void *ptr)
{
	struct header *header = (struct header *)((u32)ptr - sizeof(struct header));
	if (header->magic != MAGIC_CHECK) {
		printk ("Memory corruption!\n");
		return;
	}
	header->used = 0;
	if (header->next && header->next->used == 0)
		merge_next(header);
	if(header->prev && header->prev->used == 0)
		merge_prev(header);
	print_blocks();
}

void print_blocks()
{
	int i;
	struct header *t;
	for_each_block(t, i) {
		if (t->magic != MAGIC_CHECK) {
			printk("Memory corrupted!\n");
			return;
		}
		printk("(%x, %d, %s)-->", t, t->size, t->used?"used":"unused");
	}
	printk("end\n");
}
