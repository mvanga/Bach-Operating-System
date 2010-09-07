interrupt_vectors:
	b .
	b .
	b .
	b .
	b .
	b .
	b .
	b .

.comm stack, 0x100000
_start:
	.globl _start
	ldr sp, =stack+0x100000
	bl kernel_main
1:
	b 1b
