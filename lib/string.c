#include "string.h"
void  memset(void *s, u8 c, u16 n)
{
#ifdef x86_64

#else
	u16 i;
	u8 *ss = s;
	for (i = 0; i < n; i++)
		ss[i] = c;
#endif
}
