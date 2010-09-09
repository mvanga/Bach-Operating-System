.section ".text.boot"
.global interrupt_vectors
.extern vectors
.extern kernel_main

#include <bach/irq.h>
.extern bach_irq_stack
.extern bach_irq_handler
.extern jiffies

interrupt_vectors:
	b _start_bach       /* Reset */
	b _unused_vector    /* Undefined */
	b _unused_vector    /* Software IRQ */
	b _unused_vector	/* Instruction Abort */
	b _unused_vector    /* Data Abort */
	b _unused_vector    /* Unused */
	b _start_irq        /* IRQ */
	b _unused_vector    /* FIQ */

_unused_vector:
	ldr sp, =vectors
	sub sp, sp, #10
	adr r0, unused_msg
	bl kputs
	b died

_start_bach:
	/* Service mode with irq & fiq disabled */
	mov r0, #0xd3
	msr     cpsr, r0
	/* Setup stack pointer */
	ldr sp, =vectors
	sub sp, sp, #10
	bl kernel_main
	b died

_start_irq:
	ldr r13, =bach_irq_stack + BACH_IRQ_STACKSIZE * 4
	/* Save registers on stack */
	stmdb r13!, {r0-r3, lr}
	/* Increment jiffies */
	ldr r1, =jiffies
	ldr r0, [r1]
	add r0, r0, #1
	str r0, [r1]
	/* Call C IRQ handler */
	bl bach_irq_handler
	/* Restore the registers from stack*/
	ldmia r13!, {r0-r3, lr}
	subs pc, lr, #4
	b died

died:
	adr r0, died_msg
	bl kputs
0:
	b 0b	/* Loop forever. We're dead! */

unused_msg: .asciz "Unused vector was called\n"
died_msg: .asciz "Panic! Bach died.\n"
