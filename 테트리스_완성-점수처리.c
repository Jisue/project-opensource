#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "block.h"

#define BOARD_HEIGHT 20
#define BOARD_WIDTH 10
#define BOARD_X 4
#define BOARD_Y 2

int static score = 0;
int static level = 1;
int curX, curY;
int board[BOARD_HEIGHT + 1][BOARD_WIDTH + 2] = { 0, };

/*
void Remove_cursor(void)
함수기능: 콘솔창 커서가 보이지 않게 바꾼다.
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
void Initial(int x, int y)
함수 인자 기능
x: 커서 좌표의 x 값을 저장한다.
y: 커서 좌표의 y 값을 저장한다.
함수기능: 커서를 원하는 좌표로 이동시킨다.
*/
void Initial(int x, int y)
{
   curX = x;
   curY = y;
   Set_cursor(x, y);
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
      Initial(CBLOCK_X, CBLOCK_Y);
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