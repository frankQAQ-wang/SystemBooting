#include "boot.h"
	.code16
	.section .boottext,"ax",@progbits
#if ((BOOT_START >= CODE_START + CODE_LEN) ||( BOOT_START + BOOT_LEN <= CODE_START))
start:
	ljmp $0x0, $(BOOT_START + processmove - start)
processmove:
	mov %cs, %ax
	mov %ax, %ds
	mov %ax, %ss
	mov $0xffff, %bp
	mov $0xffff, %sp
	mov $0x0, %ax
        mov %ax, %es
        mov $0x2, %ah
        mov $(CODE_LEN / 512), %al
        mov $0x0, %ch
        mov $0x1, %cl
        mov $0x0, %dh
        mov $0x80, %dl
        mov $CODE_START, %bx
        int $0x13
	mov $(BOOT_START + failmsg - start), %bp  
	mov $(failmsgend - failmsg), %cx  
	jc printstr
	mov $(CODE_START + goto - start), %ax
	jmp *%ax
goto:
	mov $(STACK_START + STACK_LEN - 1), %bp
	mov $(STACK_START + STACK_LEN - 1), %sp
	calll main	
	mov $(CODE_START + backmsg - start), %bp  
	mov $(backmsgend - backmsg), %cx  
	call printstr
	jmp loop
printstr:	
	call clear
	mov %cs, %ax  
    	mov %ax, %es
	mov $80, %ax
	mov %cx, %bx
	sub %bx, %ax
	mov $2, %bh
	div %bh
	sub $1, %al
	mov $11, %dh  
	mov %al, %dl  
	mov $0x01, %al  
	mov $0x13, %ah  
	mov $0x0c, %bl  
	mov $0x00, %bh
    	int $0x10
	ret
clear:
	mov $0x0, %ah
	mov $0x3, %al
	int $0x10
	ret
	/*mov $0x6, %ah
    	mov $0x0, %al
	mov $0, %ch
	mov $0, %cl
	mov $24, %dh
	mov $79, %dl
	mov $0x07, %bh
	int $0x10
	ret*/
loop:
	jmp loop
failmsg:  
    	.asciz  "Fail to mov get data. "  
failmsgend:
backmsg:
	.asciz  "Why did you go back? "
backmsgend:
.org 510
.word 0xaa55
#endif
