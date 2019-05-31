#include "print.h"

/*
void Print_scorelevel(void)
함수 기능: 지정된 위치에 현재 점수와 레벨을 출력해주는 함수이다.
*/
void Print_scorelevel(void)
{
	Set_cursor(40, 3);
	printf("★레벨10 게임 클리어★");
	Set_cursor(40, 5);
	printf("레벨:%d\n", level); //레벨 출력
	Set_cursor(40, 7);
	printf("점수:%d\n", score); //점수 출력
}

/*
void Count_score(void)
함수 기능: 점수가 올라갔을 때 현재 점수와 레벨을 증가시키는 함수이다.
*/
void Count_score(void)
{
	score += 10;
	if (score % 30 == 0) //점수가 30점 오를때 마다 레벨과 속도 변경.
	{
		level += 1;
		speed -= 30; //레벨이 올라가면 블록이 떨어지는 속도를 증가함.
	}
	Print_scorelevel();
}

/*
void Print_expain(void)
함수 기능: 게임 조작법에 대한 정보를 출력해주는 함수이다.
*/
void Print_expain(void)
{
   setCursor(40,13);
   printf("게임 조작법");
   setCursor(40,15);
   printf("블록 회전: 방향키(↑)");
   setCursor(40,17);
   printf("블록 이동: 방향키(←,→)");
   setCursor(40,19);
   printf("블록 하강: Space Bar");
}