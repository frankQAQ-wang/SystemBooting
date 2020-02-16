#ifndef BOOT_H
#define BOOT_H
#ifndef __ASSEMBLY__
asm(".code16gcc");
#endif
#define BOOT_START 0x7c00
#define BOOT_LEN 0x200
#define CODE_START 0x500
#define CODE_LEN 0x6000
#define DATA_START 0x6500
#define DATA_LEN 0x4000
#define STACK_START 0xa500
#define STACK_LEN 0x5000
#endif
