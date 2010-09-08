.section ".text.boot"
.global interrupt_vectors
.extern vectors
.extern kernel_main

interrupt_vectors:
	b _unused_vector       /* Reset */
	b _unused_vector    /* Undefined */
	b _unused_vector    /* Software IRQ */
	b _unused_vector	/* Instruction Abort */
	b _unused_vector    /* Data Abort */
	b _unused_vector    /* Unused */
	b _unused_vector    /* IRQ */
	b _unused_vector    /* FIQ */

_unused_vector:
	ldr sp, =vectors
	sub sp, sp, #10
	adr r0, unused_msg
	bl puts
	b died

_start_bach:
	/* Service mode with irq & fiq disabled */
	mov r0, #0xd3
	msr     cpsr, r0
	/* Setup stack pointer */
	ldr sp, =vectors
	sub sp, sp, #10
	bl kernel_main
died:
	adr r0, died_msg
	bl puts
0:
	b 0b	/* Loop forever. We're dead! */

unused_msg: .asciz "Unused vector was called\n"
died_msg: .asciz "Panic! Bach died.\n"
