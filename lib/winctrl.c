#include "regs.h"
#include "winctrl.h"
void winclear(u8 background_color, u8 foreground_color)
{
	union win_text text[WINX * WINY];
	u16 i;
	for(i = 0; i < WINX * WINY; i++)
	{
		text[i].blink = !Blink;
		text[i].background_color = background_color;
		text[i].foreground_color = foreground_color;
		text[i].ch = ' ';
	}
	winreset(text);
}

void winreset(union win_text *text)
{
#ifdef BIOS_INT_10 //走bios中断
	struct biosregs ireg, oreg;
	initregs(&ireg);
	ireg.ah = 0x13;
	ireg.al = 0x3;
	ireg.bh = 0x0;
	ireg.cx = WINX * WINY;
	ireg.dh = 0;
	ireg.dl = 0;
	ireg.es = ds();
	ireg.bp = (u32)text;
	intcall(0x10, &ireg, &oreg);
	//写满会翻页，置回显示页数
	initregs(&ireg);
	ireg.ah = 0x5;
	ireg.al = 0;
	intcall(0x10, &ireg, &oreg);
#else //写显存
	u16 segment, addr, size;
	segment = VGA_START_ADDR >> 4;
	addr = segment & 0xf;
	size = WINX * WINY;
	asm volatile("mov %%es, %%bx; mov %%ax, %%es; rep movsw; mov %%bx, %%es"
			:
			:"a"(segment), "c"(size), "S"(text), "D"(addr)
			:"bx"
		     );
#endif
	winset_cursor(0, 0);
}

void winshow_cursor()
{
#ifdef BIOS_INT_10
#else
	u8 val;
	outb(0xa, 0x03d4);
	val = inb(0x03d5);
	val = val & 0xdf;
	outb(val, 0x03d5);
#endif
}

void winhide_cursor()
{
#ifdef BIOS_INT_10
#else
	u8 val;
	outb(0xa, 0x03d4);
	val = inb(0x03d5);
	val = val | 0x20;
	outb(val, 0x03d5);
#endif
}

u8 wincursor_ishide()
{
#ifdef BIOS_INT_10
#else
	u8 val;
	outb(0xa, 0x03d4);
	val = inb(0x03d5);
	return val & 0x20;
#endif

}

void winget_cursor(u8 *x, u8 *y)
{
#ifdef BIOS_INT_10
#else 
	u8 cursor_pos_h, cursor_pos_l;
	u16 cursor_pos;
	outb(0xe, 0x03d4);
	cursor_pos_h = inb(0x03d5);
	outb(0xf, 0x03d4);
	cursor_pos_l = inb(0x03d5);
	cursor_pos = cursor_pos_h << 8 | cursor_pos_l;
	*x = cursor_pos % WINX;
	*y = cursor_pos / WINX;
#endif
}

void winset_cursor(u8 x, u8 y)
{
#ifdef BIOS_INT_10
	struct biosregs ireg, oreg;
	initregs(&ireg);
	ireg.ah = 0x2;
	ireg.bh = 0x0;
	ireg.dh = x;
	ireg.dl = y;
	intcall(0x10, &ireg, &oreg);
#else 
	u16 cursor_pos = y * WINX + x;
	outb(0xe, 0x03d4);
	outb((cursor_pos >> 8) & 0xff, 0x03d5);
	outb(0xf, 0x03d4);
	outb(cursor_pos & 0xff, 0x03d5);
#endif
}

void winset_char(union win_text *text, u8 x, u8 y)
{
#ifdef BIOS_INT_10
#else
	u16 pos;
	pos = WINX * y + x;
	pos = pos % (WINX * WINY);
	*((u16*)VGA_START_ADDR + pos) = text->val;
#endif
}
