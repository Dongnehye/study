#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

using namespace std;

#define FPS 30

#define WIDTH 20
#define HEIGHT 25

#define EMPTY 0
#define PLAYER 1
#define WALL 2
#define ENEMY 3
#define ENEMYHIGH 4

int PlayerX = WIDTH / 2;
int PlayerY = HEIGHT - 1;

int map[HEIGHT][WIDTH];

bool bDead = false;

struct enemy
{
	int speed;
	int x;
	int y;
	bool trigger;
};

void init()
{
	memset(map, EMPTY, sizeof(map));
	srand((unsigned)time(nullptr));

	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			if ((i >= 0 && j == 0) || (i >= 0 && j == WIDTH - 1))
			{
				map[i][j] = WALL;
			}
		}
	}
}

void Input()
{
	if (kbhit())
	{
		char ch = getch();
		if ((ch == 'a' || ch == 'A') && (map[PlayerY][PlayerX - 1] != WALL))
		{
			--PlayerX;
		}
		else if ((ch == 'd' || ch == 'D') && (map[PlayerY][PlayerX + 1] != WALL))
		{
			++PlayerX;
		}
	}
}

void Update()
{
	int m_enemy = 0;
	int rdnum = 0;


	if (map[PlayerY][PlayerX] == ENEMY)
	{
		bDead = true;
		return;
	}

	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			if ((j != 0 && j != WIDTH - 1) && (map[i][j] != EMPTY))
			{

				map[i + 1][j] = map[i][j];
				map[i][j] = EMPTY;
			}
		}
	}

	m_enemy = (rand() % WIDTH - 1) + 1;

	if (map[0][m_enemy] == EMPTY)
	{
		map[0][m_enemy] = ENEMY;
	}

}

void Draw()
{
	system("cls");
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			if (bDead && (i == PlayerY && j == PlayerX))
			{
				cout << "¡Ø";
			}
			else if (i == PlayerY && j == PlayerX)
			{
				cout << "£À";
			}
			else if (map[i][j] == ENEMY)
			{
				cout << "¡ä";
			}
			else if (map[i][j] == WALL)
			{
				cout << "¡à";
			}
			else if (map[i][j] == EMPTY)
			{
				cout << "  ";
			}
		}
		cout << endl;
	}
	if (bDead)
	{
		cout << "GAME OVER" << endl;
	}
}
int main()
{
	init();

	while (true)
	{
		Input();
		Update();
		Draw();
		Sleep(1000 / FPS);
	}

	return 0;
}

//#include <iostream>
//#include <stdlib.h>
//#include <time.h>
//#include <conio.h>
//#include <Windows.h>
//
//using namespace std;
//
//#define FPS 30
//
//#define WIDTH 20
//#define HEIGHT 25
//
//#define EMPTY 0
//#define PLAYER 1
//#define WALL 2
//#define ENEMY 3
//
//int PlayerX = WIDTH / 2;
//int PlayerY = HEIGHT - 1;
//
//int map[HEIGHT][WIDTH];
//
//bool bDead = false;
//
//void init()
//{
//	memset(map, EMPTY, sizeof(map));
//	srand((unsigned)time(nullptr));
//
//	for (int i = 0; i < HEIGHT; ++i)
//	{
//		for (int j = 0; j < WIDTH; ++j)
//		{
//			if ((i >= 0 && j == 0) || (i >= 0 && j == WIDTH - 1))
//			{
//				map[i][j] = WALL;
//			}
//		}
//	}
//}
//
//void Input()
//{
//	if (kbhit())
//	{
//		char ch = getch();
//		if ( (ch == 'a' || ch == 'A') && (map[PlayerY][PlayerX - 1] != WALL))
//		{
//			--PlayerX;
//		}
//		else if ((ch == 'd' || ch == 'D') && (map[PlayerY][PlayerX + 1] != WALL))
//		{
//			++PlayerX;
//		}
//	}
//}
//
//void Update()
//{
//	int m_wall = 0;
//	int rdnum = 0;
//	
//
//	if (map[PlayerY][PlayerX] == ENEMY)
//	{
//		bDead = true;
//		return;
//	}
//
//	for (int i = HEIGHT; i > 0; --i)
//	{
//		for (int j = 0; j < WIDTH; ++j)
//		{
//			if (j != 0 && j != WIDTH - 1)
//			{
//				map[i][j] = map[i - 1][j];
//				map[i - 1][j] = EMPTY;
//			}
//		}		
//	}
//
//	m_wall = (rand() % WIDTH - 1) + 1;
//
//	if (map[0][m_wall] == EMPTY)
//	{
//		map[0][m_wall] = ENEMY;
//	}
//
//}
//
//void Draw()
//{
//	system("cls");
//	for (int i = 0; i < HEIGHT; ++i)
//	{
//		for (int j = 0; j < WIDTH; ++j)
//		{
//			if (bDead && (i == PlayerY && j == PlayerX))
//			{
//				cout << "¡Ø";
//			}
//			else if (i == PlayerY && j == PlayerX)
//			{
//				cout << "£À";
//			}
//			else if (map[i][j] == ENEMY)
//			{
//				cout << "¡ä";
//			}
//			else if (map[i][j] == WALL)
//			{
//				cout << "¡à";
//			}
//			else if (map[i][j] == EMPTY)
//			{
//				cout << "  ";
//			}
//		}
//		cout << endl;
//	}
//	if (bDead)
//	{
//		cout << "GAME OVER" << endl;
//	}
//}
//int main()
//{
//	init();
//
//	while (true)
//	{
//		Input();
//		Update();
//		Draw();
//		Sleep(1000 / FPS);
//	}
//
//	return 0;
//}