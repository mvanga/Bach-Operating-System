#include <bach/alloc.h>
#include <bach/types.h>
#include <bach/serial.h>
#include <bach/system.h>

#define MAGIC_CHECK 0xDEEEDAAA

#define GROW_BUFFER_SIZE 1024

#define for_each_block(t, i) \
	for(t = head, i = 0; \
		t != NULL; \
		t=t->next, i++)

#define for_each_alloc_list_entry(l, i) \
	for(l = alloc_head, i = 0; \
		l != NULL; \
		l=l->next, i++)

struct alloc_list *alloc_head = NULL;
struct header *head = NULL;
u32 current;

struct alloc_list {
	struct header *first;
	int full : 1;
	struct alloc_list *next;
};

struct header {
	u32 magic;
	u32 size;
	void *mem;
	int used : 1;
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

void add_block(u32 size)
{
	u32 msize = size - sizeof(struct header) - sizeof(struct footer);

	struct header *h;
	h = (struct header *)simple_malloc(sizeof(struct header));
	h->magic = MAGIC_CHECK;
	h->size = msize;
	h->mem = (void *)simple_malloc(msize);
	h->next = NULL;
	h->prev = NULL;
	h->used = 0;

	struct footer *foot = (struct footer *)simple_malloc(sizeof(struct footer));
	foot->magic = MAGIC_CHECK;
	foot->head = h;

	h->foot = foot;

	struct alloc_list *alloc_entry;
	alloc_entry = (struct alloc_list *)simple_malloc(sizeof(struct alloc_list));
	alloc_entry->first = head;
	alloc_entry->full = 0;
	alloc_entry->next = alloc_head;
	alloc_head = alloc_entry;
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

	alloc_head = (struct alloc_list *)simple_malloc(sizeof(struct alloc_list));
	alloc_head->first = head;
	alloc_head->full = 0;
	alloc_head->next = NULL;
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
	int j;
	struct header *fit = NULL;
	struct alloc_list *l;
	for_each_alloc_list_entry(l, j) {
		struct header *t = l->first;
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
	}
	if (fit == NULL) {
		add_block(GROW_BUFFER_SIZE);
		return kmalloc(size);
		return NULL;
	}
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
