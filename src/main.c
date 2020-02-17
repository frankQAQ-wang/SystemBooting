#include "regs.h"
#include "winctrl.h"
#include "string.h"
#include "keyboard.h"
void main(void)
{
	u32 i = 0;
	winclear(Black, White);
	union win_text text;
	text.foreground_color = White;
	text.background_color = Black;
	text.blink = !Blink;
	while(1)
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
}
