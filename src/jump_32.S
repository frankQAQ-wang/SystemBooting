	.code16
	.text
	.globl jump_32
	.type jump_32, @function
jump_32:
	movw	$0x18, %ax
	movw	$0x20, %bx
	popw	%cx
	movl	%cr0, %edx
	orb	$0x1, %dl
	movl	%edx, %cr0
	.byte	0x66, 0xea
	.long	main32
	.word	0x10
	.code32
main32:
	movl    %eax, %ds
        movl    %eax, %es
        movl    %eax, %fs
        movl    %eax, %gs
        movl    %eax, %ss
	ltr     %bx
	xor	%eax, %eax
	movw	%cx, %ax
	pushl	%eax
	ret
	jmp main32
