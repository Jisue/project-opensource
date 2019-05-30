#ifndef __CURSOR_H__

#define __CURSOR_H__

#include <windows.h>
void Remove_cursor(void);
void Set_cursor(int x, int y);
COORD Get_cursor(void);

#endif