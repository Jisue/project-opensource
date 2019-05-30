#include <stdio.h>
#include <windows.h>
#include <stdlib.h> //
#include <time.h>
#include <conio.h>

#define BOARD_HEIGHT 20 // ┃개수
#define BOARD_WIDTH 10  // ━개수
#define BOARD_X 4 //보드 열 x좌표
#define BOARD_Y 2 //보드 행 y좌표

#define CBLOCK_X 13
#define CBLOCK_Y 2
#define DELAY 100//지연
#define RAND 4//난수

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32

int static score = 0; //게임점수
int static level = 1; //게임레벨
int static speed = 180;
int curX, curY; //콘솔커서
int board[BOARD_HEIGHT + 1][BOARD_WIDTH + 2] = { 0, };
int block_array[][4][4] = {
	/*■
	  ■■■*/
	{
		{0,0,0,0},
		{1,0,0,0},
		{1,1,1,0},
		{0,0,0,0}},
	{
		{0,0,1,0},
		{0,0,1,0},
		{0,1,1,0},
		{0,0,0,0}},
	{
		{1,1,1,0},
		{0,0,1,0},
		{0,0,0,0},
		{0,0,0,0}},
	{
		{1,1,0,0},
		{1,0,0,0},
		{1,0,0,0},
		{0,0,0,0}},
		/* 두 번째 블록
			 ■
		 ■■■     */
	{
		{0, 0, 0, 0},
		{0, 0, 1, 0},
		{1, 1, 1, 0},
		{0, 0, 0, 0} },
	{
		{0, 1, 1, 0},
		{0, 0, 1, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 0} },
	{
		{1, 1, 1, 0},
		{1, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0} },
	{
		{1, 0, 0, 0},
		{1, 0, 0, 0},
		{1, 1, 0, 0},
		{0, 0, 0, 0} },

		/* 세 번째 블록
				■
			  ■■■    */
		{
			{0, 0, 0, 0},
			{0, 1, 0, 0},
			{1, 1, 1, 0},
			{0, 0, 0, 0} },
		{
			{0, 0, 0, 0},
			{0, 1, 0, 0},
			{1, 1, 0, 0},
			{0, 1, 0, 0} },
		{
			{0, 0, 0, 0},
			{0, 0, 0, 0},
			{1, 1, 1, 0},
			{0, 1, 0, 0} },
		{
			{0, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 0, 0} },

			/* 네 번째 블록

				  ■■■■   */
			{
				{0, 1, 0, 0},
				{0, 1, 0, 0},
				{0, 1, 0, 0},
				{0, 1, 0, 0} },
			{
				{0, 0, 0, 0},
				{0, 0, 0, 0},
				{1, 1, 1, 1},
				{0, 0, 0, 0} },
			{
				{0, 1, 0, 0},
				{0, 1, 0, 0},
				{0, 1, 0, 0},
				{0, 1, 0, 0} },
			{
				{0, 0, 0, 0},
				{0, 0, 0, 0},
				{1, 1, 1, 1},
				{0, 0, 0, 0} },

				/* 다섯 번째 블록

					  ■■
					  ■■      */
				{
					{1, 1, 0, 0},
					{1, 1, 0, 0},
					{0, 0, 0, 0},
					{0, 0, 0, 0} },
				{
					{1, 1, 0, 0},
					{1, 1, 0, 0},
					{0, 0, 0, 0},
					{0, 0, 0, 0} },
				{
					{1, 1, 0, 0},
					{1, 1, 0, 0},
					{0, 0, 0, 0},
					{0, 0, 0, 0} },
				{
					{1, 1, 0, 0},
					{1, 1, 0, 0},
					{0, 0, 0, 0},
					{0, 0, 0, 0} },


					/* 여섯 번째 블록
							■■
						  ■■      */
					{
						{0, 0, 0, 0},
						{0, 1, 1, 0},
						{1, 1, 0, 0},
						{0, 0, 0, 0} },
					{
						{0, 1, 0, 0},
						{0, 1, 1, 0},
						{0, 0, 1, 0},
						{0, 0, 0, 0} },
					{
						{0, 0, 0, 0},
						{0, 1, 1, 0},
						{1, 1, 0, 0},
						{0, 0, 0, 0} },
					{
						{0, 1, 0, 0},
						{0, 1, 1, 0},
						{0, 0, 1, 0},
						{0, 0, 0, 0} },

						/* 일곱 번째 블록

							  ■■
								■■    */
						{
							{0, 0, 0, 0},
							{1, 1, 0, 0},
							{0, 1, 1, 0},
							{0, 0, 0, 0} },
						{
							{0, 0, 1, 0},
							{0, 1, 1, 0},
							{0, 1, 0, 0},
							{0, 0, 0, 0} },
						{
							{0, 0, 0, 0},
							{1, 1, 0, 0},
							{0, 1, 1, 0},
							{0, 0, 0, 0} },
						{
							{0, 0, 1, 0},
							{0, 1, 1, 0},
							{0, 1, 0, 0},
							{0, 0, 0, 0} },

};
void Remove_cursor(void)
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void Set_cursor(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
COORD Get_cursor(void)
{
	COORD cur;
	CONSOLE_SCREEN_BUFFER_INFO curInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	cur.X = curInfo.dwCursorPosition.X;
	cur.Y = curInfo.dwCursorPosition.Y;
	return cur;
}
//void showBlock(int rotation);

void Show_board(void)
{
	int x, y;

	//중앙 보드 라인
	for (x = 1; x <= BOARD_WIDTH + 1; x++)
	{
		board[BOARD_HEIGHT][x] = 1; //board 배열 중앙 1인식
		Set_cursor((BOARD_X)+x * 2, BOARD_Y + BOARD_HEIGHT);  //콘솔좌표
		printf("━");
	}
	//왼쪽 보드 라인
	for (y = 0; y < BOARD_HEIGHT + 1; y++)
	{
		board[y][0] = 1; //board 배열 왼쪽 1인식
		Set_cursor(BOARD_X, BOARD_Y + y);
		if (y == BOARD_HEIGHT)
		{
			printf("┗");
		}
		else
		{
			printf("┃");
		}
	}
	//오른쪽 보드 라인
	for (y = 0; y < BOARD_HEIGHT + 1; y++)
	{
		board[y][BOARD_WIDTH + 1] = 1; //board 배열 오른쪽 1인식
		Set_cursor(BOARD_X + (BOARD_WIDTH + 2) * 2, BOARD_Y + y);
		if (y == BOARD_HEIGHT)
		{
			printf("┛");
		}
		else
		{
			printf("┃");
		}
	}

	//모서리값 값 변경
	board[20][0] = 1;
	board[20][11] = 1;

	puts(" ");
}

void Initial(int x, int y)
{
	curX = x;
	curY = y;
	Set_cursor(x, y);
}

//removeBlock함수 작동전 벽인 or 아닌지확인
int Detect(int block, int move1, int move2)
{
	int x, y;
	int arrX, arrY; //배열좌표저장
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
			{
				return 1;  //보드와 벽돌 겹침
			}
		}
	}
	return 0;  //겹치지 않음

}

/*
void Show_block(int block)
함수 기능: 블록 모양을 인자로 받아서 게임벽 안에서 block의 배열값을 확인하여 블록을 나타나게 해주는 함수이다.
*/
void Show_block(int block)
{
	int x, y;
	COORD cursor = Get_cursor();
	int collision;

	collision = Detect(block, 0, 0); // 벽과 충돌하는지 검사
	if (collision == 0)
	{
		//콘솔창위치 설정
		for (y = 0; y < 4; y++)
		{
			for (x = 0; x < 4; x++)
			{
				Set_cursor(cursor.X + (x * 2), cursor.Y + y);
				if (block_array[block][y][x] == 1) //배열값에서 1은 ■출력, 0은 출력없음
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
함수 기능: 블록모양을 위한 변수 rotation과 양옆으로 움직일 거리만큼 move1, move2를 인자로 받아서 새로운 위치에 showBlock함수를 이용하기 전에 블록을 지워주는 함수이다.
*/
void Remove_block(int block, int move1, int move2)
{
	int collision;
	int x, y;

	COORD cursor = Get_cursor();

	collision = Detect(block, move1, move2); //블록이 이동할 곳이 벽과 충돌하는지 검사

	if (collision == 0)
	{
		//콘솔창위치 설정
		for (y = 0; y < 4; y++)
		{
			for (x = 0; x < 4; x++)
			{
				Set_cursor(cursor.X + (x * 2), cursor.Y + y);
				if (block_array[block][y][x] == 1) //배열값이 1이면 기존 블록을 지움
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
함수 기능: 블록이 이동할 자리의 배열 값을 1로 바꿔주는 함수이다.
*/
void Board_Conginition(int n, int move1, int move2) //블록모양을 결정하는 int형 변수 n, 좌우 움직임을 표현하는 int형 변수 move1,move2
{
	COORD pos = Get_cursor();

	int arrX = pos.X + move1;  //콘솔좌표 열
	int arrY = pos.Y + move2;  //콘솔좌표 행
	int x, y;

	//커서위치정보를 배열위치정보 변경
	arrX = arrX / 2 - 2; //배열 열 변환값
	arrY = arrY - 2;	 //배열 행 변환값

	//콘솔창위치 설정
	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{
			if (block_array[n][y][x] == 1) //보드판에서 블록 이동시 1인식해서 바꿈
			{
				board[arrY + y][arrX + x] = 1;
			}
		}
	}
	return;

}

/*
void Array_down(int column)
함수 기능: int형 변수 colum을 인자로 받아서 colum을 기준으로 블록배열을 밑으로 한 칸 이동시켜주는 함수이다.
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
			if (board[y][x] == 1) //1값에 ■출력, 0은 비움.
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
		speed -= 30; // 레벨이 올라가면 블록이 떨어지는 속도를 증가함.
	}
	Print_scorelevel();
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

int Game_win(void)
{
	if (level == 10)
	{
		return 1; //게임승
	}
	else
	{
		return 0;
	}
}

void Run(void)
{

	int block;
	int key;
	int collision_rotation;

	srand(time(NULL));

	/*게임 시작~끝*/
	while (1)
	{
		Initial(CBLOCK_X, CBLOCK_Y); //블록 생성 위치 좌표 

		block = (rand() % RAND) * 4;//난수생성
		block = rand() % RAND;
		block = rand() % 7;//블록 모양 결정
		block = block * 4;
		block = 6;

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

		/*블록 한개 위~밑 이동*/
		while (1)
		{
			int last_line = 0;
			int block_rotation = 0;

			/*블록 아래로 이동*/
			while (!_kbhit())
			{
				//블록 쇼
				Show_block(block);
				//딜레이 타임
				Sleep(DELAY + speed);
				//아래이동시 1있느지 확인
				if (Detect(block, 0, 1) == 1)
				{
					last_line = 1;
					Board_Conginition(block, 0, 0);//보드 벽돌 배열 1추가
					Check_line();
					break;
				}
				Remove_block(block, 0, 1);  //board배열 +1행 
			}
			/*detect함수에서 배열값 1발견시 중지*/
			if (last_line == 1)
			{
				break;
			}

			key = _getch();
			/*방향키*/
			switch (key)
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
				// 첫수를구한다.
				block_rotation = block / 4;
				block_rotation *= 4;

				// 다음수가 끝수이하인가?
				if ((block + 1) <= (block_rotation + 3))
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
					if (Detect(block, 0, 1) == 1)
					{
						Show_block(block);
						Board_Conginition(block, 0, 0);
						break;
					}
				}
			}
		}
	}
}

int main()
{
	Remove_cursor(); //커서 깜박이 제거
	Show_board(); //보드 출력
	Print_scorelevel();
	Run(); //보드 출력 움직임
	getchar();
}