#include "regs.h"
#include "string.h"
void main(void)
{
	struct biosregs ireg, oreg;
	char*str="Hello world!";
	initregs(&ireg);
	ireg.bp=(u32)str;
	ireg.cx=12;
	ireg.dh=0x0;
	ireg.dl=0x0;
	ireg.al=0x01;
	ireg.ah=0x13;
	ireg.bl=0xc;
	ireg.bh=0x0;
	intcall(0x10, &ireg, &oreg);
	while(1);
}
