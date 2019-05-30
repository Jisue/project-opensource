#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include "cursor.h"
#include "board.h"
#include "block.h"
#include "scorelevel.h"

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
         Sleep(DELAY);
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