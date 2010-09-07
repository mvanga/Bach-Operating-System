.section ".text.vectors"
.global vectors
.global _start
.extern interrupt_vectors

_start:
vectors:
	.rep 8
	ldr pc, [pc, #24]
	.endr

.word  interrupt_vectors + 0x00
.word  interrupt_vectors + 0x04
.word  interrupt_vectors + 0x08
.word  interrupt_vectors + 0x0c
.word  interrupt_vectors + 0x10
.word  interrupt_vectors + 0x14
.word  interrupt_vectors + 0x18
.word  interrupt_vectors + 0x1c
