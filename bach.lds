
OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH("arm")
ENTRY(_start)

SECTIONS
{
	. = 0x10000;
	.text.vectors : { *(.text.vectors); }
	.text.boot : { *(.text.boot); }
	.text : { *(.text); }
	.rodata : { *(.rodata); }
	.data : { *(.data); }
	. = ALIGN(16);
	__bss_start = .;
	.bss : { *(.bss); }
	. = ALIGN(16);
	__bss_end = .;
}
