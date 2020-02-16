/*
 * setup.ld
 *
 * Linker script for the i386 setup code
 */
OUTPUT_FORMAT("elf32-i386", "elf32-i386", "elf32-i386")
OUTPUT_ARCH(i386)
ENTRY(main)

SECTIONS
{
	. = 0x500;
	.bootext	: {*(.boottext)}
	.text		: {*(.text)}
	.rodata		: { *(.rodata) }
}
