#ifndef PRINT_H
#define PRINT_H
#include "type.h"
#include "boot.h"
#include "winctrl.h"
int printstr(union win_text *text, u8 x, u8 y, char *str);
int printhex(union win_text *text, u8 x, u8 y, u32 val);
#endif
