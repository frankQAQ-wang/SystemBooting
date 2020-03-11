#include "regs.h"
#include "winctrl.h"
#include "string.h"
#include "keyboard.h"
#include "print.h"
#include "detect_memory.h"
void main(void)
{
	u32 i = 0;
	winclear(Black, White);
	union win_text text;
	struct e820entry entry[E820_MAX];
	u32 count;
	text.foreground_color = White;
	text.background_color = Black;
	text.blink = !Blink;
	/*while(1)
	{
		text.ch = kb_getchar();
		if(text.ch == 0x8)
		{
			if(i == 0)
				continue;
			i--;
			text.ch = ' ';
			winset_char(&text, (i % (WINX * WINY)) % WINX, (i % (WINX * WINY)) / WINX);
			winset_cursor((i % (WINX * WINY)) % WINX, (i % (WINX * WINY)) / WINX);
			continue;
		}
		winset_char(&text, (i % (WINX * WINY)) % WINX, (i % (WINX * WINY)) / WINX);
		i++;
		winset_cursor((i % (WINX * WINY)) % WINX, (i % (WINX * WINY)) / WINX);
	}
	count = detect_memory_e820(entry);
	for(i = 0; i < count; i++)
	{
		printhex(&text, 0, i, entry[i].haddr);
		printhex(&text, 9, i, entry[i].laddr);
		printhex(&text, 18, i, entry[i].hsize);
		printhex(&text, 27, i, entry[i].lsize);
		printhex(&text, 36, i, entry[i].type);
	}	
	while(1);*/
	jump32_func();
}
