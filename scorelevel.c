#include "scorelevel.h"

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
함수 기능: 점수가 올라갔을때 현재 점수와 레벨을 증가시키는 함수이다.
*/
void Count_score(void)
{
	score += 10;
	if (score % 30 == 0) //점수가 30점 오를때마다 레벨과 속도 변경.
	{
		level += 1;
		speed -= 30; //레벨이 올라가면 블록이 떨어지는 속도를 증가함.
	}
	Print_scorelevel();
}