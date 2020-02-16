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
	mov $CODE_START, %ax
	add $(goto - start), %ax
	jmp *%ax
goto:
	mov $(STACK_START + STACK_LEN - 1), %bp
	mov $(STACK_START + STACK_LEN - 1), %sp
	call main	
	mov $(BOOT_START + backmsgend - start), %bp  
	mov $(backmsgend - backmsg), %cx  
	jmp printstr	
printstr:
	mov %cs, %ax  
    	mov %ax, %es  
	mov $0x00, %dh  
	mov $0x00, %dl  
	mov $0x01, %al  
	mov $0x13, %ah  
	mov $0x0c, %bl  
	mov $0x00, %bh  
    	int $0x10  
loop:
	jmp loop
failmsg:  
    	.asciz  "Fail to mov get data\n"  
failmsgend:
backmsg:
	.asciz  "Why did you go back?\n"
backmsgend:
.org 510
.word 0xaa55
#endif
