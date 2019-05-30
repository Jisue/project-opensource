#include <stdio.h>
#include <windows.h>
#include <stdlib.h> //
#include <time.h>
#include <conio.h>

#define BOARD_HEIGHT 20 // ������
#define BOARD_WIDTH 10  // ������
#define BOARD_X 4 //���� �� x��ǥ
#define BOARD_Y 2 //���� �� y��ǥ

#define CBLOCK_X 13
#define CBLOCK_Y 2
#define DELAY 100//����
#define RAND 4//����

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32

int static score = 0; //��������
int static level = 1; //���ӷ���
int static speed = 180;
int curX, curY; //�ܼ�Ŀ��
int board[BOARD_HEIGHT + 1][BOARD_WIDTH + 2] = { 0, };
int block_array[][4][4] = {
	/*��
	  ����*/
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
		/* �� ��° ���
			 ��
		 ����     */
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

		/* �� ��° ���
				��
			  ����    */
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

			/* �� ��° ���

				  �����   */
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

				/* �ټ� ��° ���

					  ���
					  ���      */
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


					/* ���� ��° ���
							���
						  ���      */
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

						/* �ϰ� ��° ���

							  ���
								���    */
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

	//�߾� ���� ����
	for (x = 1; x <= BOARD_WIDTH + 1; x++)
	{
		board[BOARD_HEIGHT][x] = 1; //board �迭 �߾� 1�ν�
		Set_cursor((BOARD_X)+x * 2, BOARD_Y + BOARD_HEIGHT);  //�ܼ���ǥ
		printf("��");
	}
	//���� ���� ����
	for (y = 0; y < BOARD_HEIGHT + 1; y++)
	{
		board[y][0] = 1; //board �迭 ���� 1�ν�
		Set_cursor(BOARD_X, BOARD_Y + y);
		if (y == BOARD_HEIGHT)
		{
			printf("��");
		}
		else
		{
			printf("��");
		}
	}
	//������ ���� ����
	for (y = 0; y < BOARD_HEIGHT + 1; y++)
	{
		board[y][BOARD_WIDTH + 1] = 1; //board �迭 ������ 1�ν�
		Set_cursor(BOARD_X + (BOARD_WIDTH + 2) * 2, BOARD_Y + y);
		if (y == BOARD_HEIGHT)
		{
			printf("��");
		}
		else
		{
			printf("��");
		}
	}

	//�𼭸��� �� ����
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

//removeBlock�Լ� �۵��� ���� or �ƴ���Ȯ��
int Detect(int block, int move1, int move2)
{
	int x, y;
	int arrX, arrY; //�迭��ǥ����
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
				return 1;  //����� ���� ��ħ
			}
		}
	}
	return 0;  //��ġ�� ����

}

/*
void Show_block(int block)
�Լ� ���: ��� ����� ���ڷ� �޾Ƽ� ���Ӻ� �ȿ��� block�� �迭���� Ȯ���Ͽ� ����� ��Ÿ���� ���ִ� �Լ��̴�.
*/
void Show_block(int block)
{
	int x, y;
	COORD cursor = Get_cursor();
	int collision;

	collision = Detect(block, 0, 0); // ���� �浹�ϴ��� �˻�
	if (collision == 0)
	{
		//�ܼ�â��ġ ����
		for (y = 0; y < 4; y++)
		{
			for (x = 0; x < 4; x++)
			{
				Set_cursor(cursor.X + (x * 2), cursor.Y + y);
				if (block_array[block][y][x] == 1) //�迭������ 1�� �����, 0�� ��¾���
				{
					printf("��");
				}
			}
		}
		Set_cursor(cursor.X, cursor.Y);
	}
}

/*
void Remove_block(int block, int move1, int move2)
�Լ� ���: ��ϸ���� ���� ���� rotation�� �翷���� ������ �Ÿ���ŭ move1, move2�� ���ڷ� �޾Ƽ� ���ο� ��ġ�� showBlock�Լ��� �̿��ϱ� ���� ����� �����ִ� �Լ��̴�.
*/
void Remove_block(int block, int move1, int move2)
{
	int collision;
	int x, y;

	COORD cursor = Get_cursor();

	collision = Detect(block, move1, move2); //����� �̵��� ���� ���� �浹�ϴ��� �˻�

	if (collision == 0)
	{
		//�ܼ�â��ġ ����
		for (y = 0; y < 4; y++)
		{
			for (x = 0; x < 4; x++)
			{
				Set_cursor(cursor.X + (x * 2), cursor.Y + y);
				if (block_array[block][y][x] == 1) //�迭���� 1�̸� ���� ����� ����
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
�Լ� ���: ����� �̵��� �ڸ��� �迭 ���� 1�� �ٲ��ִ� �Լ��̴�.
*/
void Board_Conginition(int n, int move1, int move2) //��ϸ���� �����ϴ� int�� ���� n, �¿� �������� ǥ���ϴ� int�� ���� move1,move2
{
	COORD pos = Get_cursor();

	int arrX = pos.X + move1;  //�ܼ���ǥ ��
	int arrY = pos.Y + move2;  //�ܼ���ǥ ��
	int x, y;

	//Ŀ����ġ������ �迭��ġ���� ����
	arrX = arrX / 2 - 2; //�迭 �� ��ȯ��
	arrY = arrY - 2;	 //�迭 �� ��ȯ��

	//�ܼ�â��ġ ����
	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{
			if (block_array[n][y][x] == 1) //�����ǿ��� ��� �̵��� 1�ν��ؼ� �ٲ�
			{
				board[arrY + y][arrX + x] = 1;
			}
		}
	}
	return;

}

/*
void Array_down(int column)
�Լ� ���: int�� ���� colum�� ���ڷ� �޾Ƽ� colum�� �������� ��Ϲ迭�� ������ �� ĭ �̵������ִ� �Լ��̴�.
*/
void Array_down(int column)
{
	int y, x;

	//board�迭 ���� ��������� ������ �̵�
	for (y = column; y >= 0; y--)
	{
		for (x = 1; x <= 10; x++)
		{
			board[y][x] = board[y - 1][x];
		}
	}
	//1�� ��������Ƿ� ���� ��� ���������� ���. 
	for (x = 1; x <= 10; x++)
	{
		board[0][x] = 0;
	}

	//board�迭�� ���
	for (y = 1; y <= 19; y++) //19����� 1����� �˻�
	{
		for (x = 1; x <= 10; x++)//1������ 10������ �˻�
		{
			Set_cursor((BOARD_X)+x * 2 + 1, y + BOARD_Y);
			if (board[y][x] == 1) //1���� �����, 0�� ���.
			{
				printf("��");
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
�Լ� ���: ������ ��ġ�� ���� ������ ������ ������ִ� �Լ��̴�.
*/
void Print_scorelevel(void)
{
	Set_cursor(40, 3);
	printf("�ڷ���10 ���� Ŭ�����");
	Set_cursor(40, 5);
	printf("����:%d\n", level); //���� ���
	Set_cursor(40, 7);
	printf("����:%d\n", score); //���� ���
}

/*
void Count_score(void)
�Լ� ���: ������ �ö����� ���� ������ ������ ������Ű�� �Լ��̴�.
*/
void Count_score(void)
{
	score += 10;
	if (score % 30 == 0) //������ 30�� ���������� ������ �ӵ� ����.
	{
		level += 1;
		speed -= 30; // ������ �ö󰡸� ����� �������� �ӵ��� ������.
	}
	Print_scorelevel();
}

/*
void Check_line(void)
�Լ� ���: ���� ��ü�� �˻��ϸ鼭 ���� ��ƴ���� ���� ������ �ش� ���� �����ϰ� ������ �ο��Ѵ�.
*/
void Check_line(void)
{
	int block_num;
	int x, y;

	for (y = 19; y >= 1; y--) //19����� 1����� �˻�
	{
		block_num = 0;
		for (x = 1; x < 11; x++) //1������ 10������ �˻�
		{
			if (board[y][x] == 1)
			{
				block_num++;
				if (block_num == 10) //��ƴ���� ���� ������
				{
					for (x = 1; x < 11; x++) //�ش� �� ����
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
		return 5; //���� ����
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
		return 1; //���ӽ�
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

	/*���� ����~��*/
	while (1)
	{
		Initial(CBLOCK_X, CBLOCK_Y); //��� ���� ��ġ ��ǥ 

		block = (rand() % RAND) * 4;//��������
		block = rand() % RAND;
		block = rand() % 7;//��� ��� ����
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

		/*��� �Ѱ� ��~�� �̵�*/
		while (1)
		{
			int last_line = 0;
			int block_rotation = 0;

			/*��� �Ʒ��� �̵�*/
			while (!_kbhit())
			{
				//��� ��
				Show_block(block);
				//������ Ÿ��
				Sleep(DELAY + speed);
				//�Ʒ��̵��� 1�ִ��� Ȯ��
				if (Detect(block, 0, 1) == 1)
				{
					last_line = 1;
					Board_Conginition(block, 0, 0);//���� ���� �迭 1�߰�
					Check_line();
					break;
				}
				Remove_block(block, 0, 1);  //board�迭 +1�� 
			}
			/*detect�Լ����� �迭�� 1�߽߰� ����*/
			if (last_line == 1)
			{
				break;
			}

			key = _getch();
			/*����Ű*/
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
				// ù�������Ѵ�.
				block_rotation = block / 4;
				block_rotation *= 4;

				// �������� ���������ΰ�?
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
	Remove_cursor(); //Ŀ�� ������ ����
	Show_board(); //���� ���
	Print_scorelevel();
	Run(); //���� ��� ������
	getchar();
}