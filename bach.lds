
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

	. = ALIGN(16);
	__exitcall_begin = .;
	.text.exitcall :
	{
		*(.exitcall0.exit);
	}
	__exitcall_end = .;

	. = ALIGN(16);
	__initcall_begin = .;
	.text.initcall :
	{
		*(.initcall0.init);
	}
	__initcall_end = .;

	__alloc_begin = .;
}
