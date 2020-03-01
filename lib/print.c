#include "print.h"
int printstr(union win_text *text, u8 x, u8 y, char *str)
{
	char *s = str;
	u16 pos;

	pos = y * WINX + x;
	pos = pos % (WINX * WINY);
	while(*s != '\0')
	{
		text->ch = *s;
		winset_char(text, pos % WINX, pos / WINX);
		pos++;
		s++;
		pos = pos % (WINX * WINY);
	}
	return pos;
}
int printhex(union win_text *text, u8 x, u8 y, u32 val)
{
	char str[10] = {0};
	u32 v = val;
	u32 vl = val;
	char *s = str + 8;

	do
	{
		v = vl % 16;
		vl = vl / 16;
		if(v < 10)
			*s = v + '0';
		else
			*s = v - 10 + 'a';	
		s--;
	}while(vl != 0);
	s++;
	return printstr(text, x, y, s);
}
