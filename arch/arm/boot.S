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
	b _undef_vector      /* Undefined */
	b _soft_irq         /* Software IRQ */
	b _instruct_abort	/* Instruction Abort */
	b _data_abort       /* Data Abort */
	b _unused_vector    /* Unused */
	b _start_irq        /* IRQ */
	b _start_fiq        /* FIQ */

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

_undef_vector:
	ldr sp, =vectors
	sub sp, sp, #10
	adr r0, undef_vector_msg
	bl kputs
	b died

_soft_irq:
	ldr sp, =vectors
	sub sp, sp, #10
	adr r0, soft_irq_msg
	bl kputs
	b died

_instruct_abort:
	ldr sp, =vectors
	sub sp, sp, #10
	adr r0, instr_abort_msg
	bl kputs
	b died

_data_abort:
	ldr sp, =vectors
	sub sp, sp, #10
	#adr r0, data_abort_msg
	#bl kputs
	b died

_start_irq:
	ldr r13, =bach_irq_stack + IRQ_STACKSIZE * 4
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

_start_fiq:
	ldr sp, =vectors
	sub sp, sp, #10
	adr r0, fiq_msg
	bl kputs
	subs pc, lr, #4

died:
	adr r0, died_msg
	bl kputs
0:
	b 0b	/* Loop forever. We're dead! */

unused_msg: .asciz "Unused vector was called\n"
undef_vector_msg: .asciz "Undefined vector called\n"
soft_irq_msg: .asciz "Software interrupt called\n"
instr_abort_msg: .asciz "Instruction abort\n"
data_abort_msg: .asciz "Data abort\n"
fiq_msg: .asciz "FIQ called\n"
died_msg: .asciz "Panic! Bach died.\n"
