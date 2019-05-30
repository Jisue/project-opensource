#include "cursor.h"

/*
void Remove_cursor(void)
함수기능: 콘솔 창 커서가 보이지 않게 바꾼다.
*/
void Remove_cursor(void)
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

/*
void Set_cursor(int x, int y)
함수 인자 기능
x: 커서 좌표의 x 값을 저장한다.
y: 커서 좌표의 y 값을 저장한다.
함수기능: 커서를 원하는 좌표로 이동시킨다.
*/
void Set_cursor(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
/*
COORD Get_cursor(void)
함수기능: 커서의 좌표 정보를 얻어온다.
*/
COORD Get_cursor(void)
{
	COORD cur;
	CONSOLE_SCREEN_BUFFER_INFO curInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	cur.X = curInfo.dwCursorPosition.X;
	cur.Y = curInfo.dwCursorPosition.Y;
	return cur;
}