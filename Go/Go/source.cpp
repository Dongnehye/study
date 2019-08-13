#include <iostream>
#include <conio.h>

using namespace std;

#define WITDH 19
#define HEIGHT 19

#define EMPTY 0
#define BLACK 1
#define WHITE 2

int x = WITDH / 2;
int y = HEIGHT / 2;
int map[HEIGHT][WITDH];

bool checkWin(int color)
{
	int count = 0;
	if (y - 5 > 0)
	{
		for (int z = 0; z < 5; ++z)
		{
			if (map[y - z][x] == color)
			{
				++count;
			}
			else
				break;
		}
		if (count == 5)
		{
			return true;
		}
		else
			count = 0;
	}
	if (y + 5 < HEIGHT)
	{
		for (int z = 0; z < 5; ++z)
		{
			if (map[y + z][x] == color)
			{
				++count;
			}
			else
				break;
		}
		if (count == 5)
		{
			return true;
		}
		else
			count = 0;
	}
	if (x + 5 < WITDH)
	{
		for (int z = 0; z < 5; ++z)
		{
			if (map[y][x + z] == color)
			{
				++count;
			}
			else
				break;
		}
		if (count == 5)
		{
			return true;
		}
		else
			count = 0;
	}
	if (x - 5 > 0)
	{
		for (int z = 0; z < 5; ++z)
		{
			if (map[y][x - z] == color)
			{
				++count;
			}
			else
				break;
		}
		if (count == 5)
		{
			return true;
		}
		else
			count = 0;
	}
	if (y - 5 > 0 && x - 5 > 0)
	{
		for (int z = 0; z < 5; ++z)
		{
			if (map[y - z][x - z] == color)
			{
				++count;
			}
			else
				break;
		}
		if (count == 5)
		{
			return true;
		}
		else
			count = 0;
	}
	if (y - 5 > 0 && x + 5 > 0)
	{
		for (int z = 0; z < 5; ++z)
		{
			if (map[y - z][x + z] == color)
			{
				++count;
			}
			else
				break;
		}
		if (count == 5)
		{
			return true;
		}
		else
			count = 0;
	}
	if (y + 5 > 0 && x + 5 > 0)
	{
		for (int z = 0; z < 5; ++z)
		{
			if (map[y + z][x + z] == color)
			{
				++count;
			}
			else
				break;
		}
		if (count == 5)
		{
			return true;
		}
		else
			count = 0;
	}
	if (y + 5 > 0 && x - 5 > 0)
	{
		for (int z = 0; z < 5; ++z)
		{
			if (map[y + z][x - z] == color)
			{
				++count;
			}
			else
				break;
		}
		if (count == 5)
		{
			return true;
		}
		else
			count = 0;
	}
}

int main()
{
	char ch = NULL;
	int turn = 0;
	int color = 0;
	bool win = false;

	memset(map, EMPTY, sizeof(map));

	while (!win)
	{
		ch = getch();
		system("cls");

		if (ch == 'w' && y > 0)
			--y;
		else if (ch == 's' && y < HEIGHT - 1)
			++y;
		else if (ch == 'a' && x > 0)
			--x;
		else if (ch == 'd' && x < WITDH - 1)
			++x;
		else if (ch == 'z')
		{
			if (turn % 2 == 0)
			{
				if (map[y][x] == EMPTY)
				{
					map[y][x] = BLACK;
					color = BLACK;
					++turn;
				}
			}
			else
			{
				if (map[y][x] == EMPTY)
				{
					map[y][x] = WHITE;
					color = WHITE;
					++turn;
				}
			}
			win = checkWin(color);
		}

		for (int i = 0; i < HEIGHT; ++i)
		{
			for (int j = 0; j < WITDH; ++j)
			{
				if (i == y && j == x)
					cout << "☆";
				else if (map[i][j] == BLACK)
					cout << "○";
				else if (map[i][j] == WHITE)
					cout << "●";
				else if (i == 0 && j == 0)
					cout << "┌";
				else if (i == 0 && j == WITDH - 1)
					cout << "┐";
				else if (i == HEIGHT - 1 && j == 0)
					cout << "└";
				else if (i == HEIGHT - 1 && j == WITDH - 1)
					cout << "┘";
				else if (i == 0 && j > 0)
					cout << "┬";
				else if (i == HEIGHT - 1 && j > 0)
					cout << "┴";
				else if (i > 0 && j == 0)
					cout << "├";
				else if (i > 0 && j == WITDH - 1)
					cout << "┤";
				else
					cout << "┼";
			}
			cout << endl;
		}
		if (win)
		{
			if (turn % 2 == 0)
				cout << "백색승리입니다.";
			else
				cout << "흑색승리입니다.";
		}
		else
		{
			if (turn % 2 == 0)
				cout << "흑색턴입니다.";
			else
				cout << "백색턴입니다.";
		}
	}

	return 0;
}