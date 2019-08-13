#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <vector>

using namespace std;

#define FPS 30

#define WIDTH 25
#define HEIGHT 25

#define EMPTY 0
#define PLAYER 1
#define WALL 2
#define ENEMY 3

int PlayerX = WIDTH / 2;
int PlayerY = HEIGHT - 1;

int map[HEIGHT][WIDTH];

bool bDead = false;

struct Enemy
{
	int speed;
	int count;
	int x;
	int y;
};

vector<Enemy> venemy;
int score = 0;

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

	if (map[PlayerY][PlayerX] == ENEMY)
	{
		bDead = true;
		return;
	}
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			if (j != 0 && j != WIDTH - 1)
			{
				map[i][j] = EMPTY;
			}
		}
	}

	for (int i = 0; i < venemy.size(); ++i)
	{	
		if (venemy[i].speed <= venemy[i].count)
		{
			venemy[i].y += 1;
			venemy[i].count = 0;
		}
		else
		{
			venemy[i].count += 1;
		}
	}

	for (int i = 0; i < venemy.size(); ++i)
	{
		if (venemy[i].y > HEIGHT - 1)
		{
			score += 100;
			venemy.erase(venemy.begin() + i);
		}
		else
			map[venemy[i].y][venemy[i].x] = ENEMY;
	}

	m_enemy = (rand() % (WIDTH - 2)) + 1;
	
	if (map[0][m_enemy] == EMPTY)
	{
		Enemy inst_enemy;
		inst_enemy.count = 0;
		inst_enemy.speed = (rand() % 4) + 1;
		inst_enemy.x = m_enemy;
		inst_enemy.y = 0;

		venemy.push_back(inst_enemy);
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
	cout << score << endl;
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