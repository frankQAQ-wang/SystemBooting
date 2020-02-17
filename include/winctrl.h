#ifndef WINCTRL_H
#define WINCTRL_H
#include "boot.h"
#include "type.h"
#define Black       0x0
#define Blue        0x1
#define Green       0x2
#define Cyan        0x3
#define Red         0x4
#define Magenta     0x5
#define Brown       0x6
#define Light_Gray  0x7
#define Dark_Gray   0x8
#define Light_Blue  0x9
#define Light_Green 0xa
#define Light_Cyan  0xb
#define Light_Red   0xc
#define Pink        0xd
#define Yellow      0xe
#define White       0xf
#define Blink       0x1
#define COMBINE(blink, background_color, foreground_color, ch) (blink<<15 | background_color<<12 | foreground_color<<8 | ch)
#define WINX 80
#define WINY 25
#define VGA_START_ADDR 0xb8000
union win_text
{
	u16 val;
	struct
	{
		u8 ch;
		union
		{
			struct
			{
				u8 foreground_color:4;
				u8 background_color:3;
				u8 blink:1;
			};
			u8 attr;
		};
	};
};
void winclear(u8 background_color, u8 foreground_color);
void winreset(union win_text *text); //most for game, text? 
void winshow_cursor();
void winhide_cursor();
u8 wincursor_ishide();
void winget_cursor(u8 *x, u8 *y);
void winset_cursor(u8 x, u8 y);
void winset_char(union win_text *text, u8 x, u8 y);
#endif
