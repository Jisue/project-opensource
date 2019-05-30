#include "block.h"
#include "cursor.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_HEIGHT 20
#define BOARD_WIDTH 10
#define BOARD_X 4
#define BOARD_Y 2

#define CBLOCK_X 13
#define CBLOCK_Y 2

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32

int static score = 0;
int static level = 1;
int static speed = 180;
int curX, curY;
int board[BOARD_HEIGHT + 1][BOARD_WIDTH + 2] = { 0, };

/*
void Show_board(void)
함수기능: 콘솔창에 보드를 출력하고 보드 부분은 배열에 저장한다.
*/
void Show_board(void)
{
	int x, y;

	for (x = 1; x <= BOARD_WIDTH + 1; x++) //위 아래 보드 출력
	{
		board[BOARD_HEIGHT][x] = 1;
		Set_cursor((BOARD_X)+x * 2, BOARD_Y + BOARD_HEIGHT);
		printf("━");
	}

	for (y = 0; y < BOARD_HEIGHT + 1; y++) //왼쪽 보드와 모서리 출력
	{
		board[y][0] = 1;
		Set_cursor(BOARD_X, BOARD_Y + y);
		if (y == BOARD_HEIGHT) //모서리
		{
			printf("┗");
		}
		else
		{
			printf("┃"); //왼쪽
		}
	}
	//오른쪽 보드와 모서리 출력
	for (y = 0; y < BOARD_HEIGHT + 1; y++) //오른쪽 보드와 모서리 출력
	{
		board[y][BOARD_WIDTH + 1] = 1;
		Set_cursor(BOARD_X + (BOARD_WIDTH + 2) * 2, BOARD_Y + y);
		if (y == BOARD_HEIGHT)
		{
			printf("┛"); //모서리
		}
		else
		{
			printf("┃"); //오른쪽
		}
	}

	board[20][0] = 1;
	board[20][11] = 1;

	puts(" ");
}

/*
int Detect(int block, int move1, int move2)
함수 인자 기능
block: 블록의 모양을 결정하는 값을 저장한다.
move1: x축으로 블록을 움직일 값을 저장한다.
move2: y축으로 블록을 움직일 값을 저장한다.
함수기능: 블록을 움직이면 벽과 충돌하는지 확인한다.
*/
int Detect(int block, int move1, int move2)
{
	int x, y;
	int arrX, arrY;
	COORD pos = Get_cursor();

	arrX = pos.X + move1;
	arrY = pos.Y + move2;

	arrX = (arrX / 2) - 2;
	arrY = arrY - BOARD_Y;


	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{
			if ((block_array[block][y][x] == 1) && board[arrY + y][arrX + x] == 1)
				return 1; //보드와 블록이 충돌함 
		}
	}
	return 0;  //보드와 블록이 충돌하지 않음

}

/*
void Show_block(int block)
함수 인자 기능
blcok: 블록의 모양을 결정하는 값을 저장한다.
함수 기능: 해당 블록의 배열 값을 확인하여 출력하는 함수이다.
*/
void Show_block(int block)
{
	int x, y;
	COORD cursor = Get_cursor();
	int collision;

	collision = Detect(block, 0, 0); //벽과 충돌하는지 검사
	if (collision == 0)
	{
		//콘솔창위치 설정
		for (y = 0; y < 4; y++)
		{
			for (x = 0; x < 4; x++)
			{
				Set_cursor(cursor.X + (x * 2), cursor.Y + y);
				if (block_array[block][y][x] == 1) //해당 배열에 블록이 있으면 ■ 출력함으로써 모양에 맞는 블록을 출력
				{
					printf("■");
				}
			}
		}
		Set_cursor(cursor.X, cursor.Y);
	}
}

/*
void Remove_block(int block, int move1, int move2)
함수 인자 기능
block: 블록의 모양을 결정하는 값을 저장한다.
move1: x축으로 블록을 움직일 값을 저장한다.
move2: y축으로 블록을 움직일 값을 저장한다.
함수 기능: 새로운 위치에 블록을 출력하기 전에 블록을 지워주는 함수이다.
*/
void Remove_block(int block, int move1, int move2)
{
	int collision;
	int x, y;

	COORD cursor = Get_cursor();

	collision = Detect(block, move1, move2); //블록을 이동시킬 곳이 보드과 충돌하는지 검사

	if (collision == 0)
	{
		//콘솔창위치 설정
		for (y = 0; y < 4; y++)
		{
			for (x = 0; x < 4; x++)
			{
				Set_cursor(cursor.X + (x * 2), cursor.Y + y);
				if (block_array[block][y][x] == 1) //해당 배열에 블록이 있었으면 공백을 출력하여 블록을 지워줌
				{
					printf(" ");
				}
			}
		}
		Set_cursor(cursor.X + move1, cursor.Y + move2);
	}
}

/*
void Board_Conginition(int n, int move1, int move2)
함수 인자 기능
n: 블록의 모양을 결정하는 값을 저장한다.
move1: x축으로 블록을 움직일 값을 저장한다.
move2: y축으로 블록을 움직일 값을 저장한다.
함수 기능: 블록이 이동할 자리의 배열 값을 1로 바꿔주는 함수이다.
*/
void Board_Conginition(int n, int move1, int move2)
{
	COORD pos = Get_cursor();

	int arrX = pos.X + move1; //콘솔 좌표 열
	int arrY = pos.Y + move2; //콘솔 좌표 행
	int x, y;

	//커서위치정보를 배열위치정보 변경
	arrX = arrX / 2 - 2; //배열 열 변환 값
	arrY = arrY - 2; //배열 행 변환 값

	//콘솔창위치 설정
	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{
			if (block_array[n][y][x] == 1) //보드판에서 블록 이동시 배열에 블록이 있는지 인식해서 바꿈
			{
				board[arrY + y][arrX + x] = 1;
			}
		}
	}
	return;

}

/*
void Array_down(int column)
함수 인자 기능
colum: 행 값을 저장한다.
함수 기능: colum을 기준으로 블록배열을 밑으로 한 칸 이동시켜주는 함수이다.
*/
void Array_down(int column)
{
	int y, x;

	//board배열 값을 행기준으로 밑으로 이동
	for (y = column; y >= 0; y--)
	{
		for (x = 1; x <= 10; x++)
		{
			board[y][x] = board[y - 1][x];
		}
	}
	//1행 당겨졌으므로 전의 블록 마지막줄을 비움. 
	for (x = 1; x <= 10; x++)
	{
		board[0][x] = 0;
	}

	//board배열의 출력
	for (y = 1; y <= 19; y++) //19행부터 1행까지 검사
	{
		for (x = 1; x <= 10; x++)//1열부터 10열까지 검사
		{
			Set_cursor((BOARD_X)+x * 2 + 1, y + BOARD_Y);
			if (board[y][x] == 1) //배열에 블록이있으면 ■출력
			{
				printf("■");
			}
			else
			{
				printf("  ");
			}
		}
	}

}

/*
void Check_line(void)
함수 기능: 보드 전체를 검사하면서 만약 빈틈없는 행이 있으면 해당 행을 삭제하고 점수를 부여한다.
*/
void Check_line(void)
{
	int block_num;
	int x, y;

	for (y = 19; y >= 1; y--) //19행부터 1행까지 검사
	{
		block_num = 0;
		for (x = 1; x < 11; x++) //1열부터 10열까지 검사
		{
			if (board[y][x] == 1)
			{
				block_num++;
				if (block_num == 10) //빈틈없는 행이 있으면
				{
					for (x = 1; x < 11; x++) //해당 행 삭제
					{
						Set_cursor((x + 2) * 2, y + 2);
						printf("  ");
					}
					Count_score();
					Array_down(y);
				}

			}
		}
	}
}

/*
int Game_over(int block)
함수 인자 기능: 블록의 모양을 결정하는 값을 저장한다.
함수 기능: 만약 블록을 움직이지 않았음에도 불구하고 보드와 충돌하게 된다면 게임 오버라고 판단한다.
*/
int Game_over(int block)
{
	if (Detect(block, 0, 0))
	{
		return 5; //게임 오버
	}
	else
	{
		return 0;
	}
}

/*
int Game_win(void)
함수 기능: 만약 level의 값이 10이라면 게임 승리라고 판단한다.
*/
int Game_win(void)
{
	if (level == 10)
	{
		return 1; //게임 승리
	}
	else
	{
		return 0;
	}
}

/*void Move_block(int block)
함수 인자
block : 블록의 모양을 결정하는 값을 저장한다.
함수 기능 : 정의한 함수를 사용하여 블록을 움직인다.
*/
void Move_block(int block)
{
	int key;
	int collision_rotation;

	while (1) //블록 이동
	{
		int last_line = 0;
		int block_rotation = 0;

		while (!_kbhit()) //블록 떨어짐
		{
			Show_block(block);
			Sleep(speed);
			if (Detect(block, 0, 1) == 1) //블록 바로 밑에 보드가 있다면
			{
				last_line = 1;
				Board_Conginition(block, 0, 0);
				Check_line();
				break;
			}
			Remove_block(block, 0, 1);
		}

		if (last_line == 1)
		{
			break;
		}

		key = _getch();
		switch (key) //방향 키에 맞게 블록 이동
		{
		case LEFT:
			Remove_block(block, -2, 0);
			Show_block(block);
			break;
		case RIGHT:
			Remove_block(block, 2, 0);
			Show_block(block);
			break;
		case UP:
			block_rotation = block / 4; //기본 모양 블록을 구함
			block_rotation *= 4;

			if ((block + 1) <= (block_rotation + 3)) //회전한 모양 블록을 구함
			{
				block_rotation = block + 1;
			}

			collision_rotation = Detect(block_rotation, 0, 0);
			if (collision_rotation == 0)
			{
				Remove_block(block, 0, 0);
				block = block_rotation;
				Show_block(block);
				break;
			}
			break;
		case DOWN:
			Remove_block(block, 0, 2);
			Show_block(block);
			break;
		case SPACE:
			while (1)
			{
				Remove_block(block, 0, 1);
				if (Detect(block, 0, 1) == 1) //블록 바로 밑에 보드가 있다면
				{
					Show_block(block);
					Board_Conginition(block, 0, 0);
					break;
				}
			}
		}
	}
}

/*
int Run(void)
함수 기능
: 랜덤한 모양의 블록을 만들고 게임의 승패 여부를 확인하여 게임을 진행하거나 종료하는 기능이다.
*/
void Run(void)
{
	int block;
	srand(time(NULL));

	while (1) //게임 시작~끝
	{
		Set_cursor(CBLOCK_X, CBLOCK_Y);
		block = (rand() % 7) * 4;

		if (Game_win())
		{
			Set_cursor(35, 20);
			printf("GAME WIN");
			getchar();
			exit(1);
		}
		if (Game_over(block))
		{
			Set_cursor(35, 20);
			printf("GAME OVER");
			getchar();
			exit(1);
		}
		Move_block(block);
	}
}

int main()
{
	Remove_cursor();
	Show_board();
	Print_scorelevel();
	Run();
	getchar();
}