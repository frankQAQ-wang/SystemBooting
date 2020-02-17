#include "regs.h"
#include "keyboard.h"
u8 kb_getchar()
{
	struct biosregs ireg, oreg;
	initregs(&ireg);
	ireg.ah = 0;
	intcall(0x16, &ireg, &oreg);
	return oreg.al;
}
