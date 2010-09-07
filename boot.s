.section ".text.boot"
.global interrupt_vectors
.extern vectors
.extern kernel_main

interrupt_vectors:
	b _unused_vector
	b _unused_vector
	b _unused_vector
	b _unused_vector
	b _unused_vector
	b _unused_vector
	b _unused_vector
	b _unused_vector

_unused_vector:
	adr r0, unused_msg
	bl puts
	b died
_start_bach:
	bl kernel_main
died:
	adr r0, died_msg
	bl puts
0:
	b 0b	/* Loop forever. We're dead! */

died_msg: .asciz "Panic! Bach died.\n"
unused_msg: .asciz "Unused vector was called\n"
