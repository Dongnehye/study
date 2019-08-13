#include "Map.h"
#include <iostream>
using namespace std;

Map::Map()
{
}

Map::~Map()
{
}
void Map::Init()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
			map[i][j] = TILE_EMPTY;
	}

	for (int i = 0; i < HEIGHT; i++)
	{
		map[i][0] = TILE_WALL;
		map[i][WIDTH - 1] = TILE_WALL;
	}

	for (int j = 0; j < WIDTH; j++)
	{
		map[0][j] = TILE_WALL;
		map[HEIGHT - 1][j] = TILE_WALL;
	}
}
void Map::DrawMap()
{
	system("cls");
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			switch (map[i][j])
			{
			case TILE_EMPTY:
				cout << "  ";
				break;
			case TILE_WALL:
				cout << "бс";
				break;
			case TILE_PLAYER:
				cout << "б┘";
				break;
			}
		}
		cout << endl;
	}
}
//
//void Map::CreateTreasure()
//{
//	int m_x = 0;
//	int m_y = 0;
//
//	srand((unsigned int)time(0));
//	TreausreNum = rand() % MAXNUMTREASURE;
//
//	while (true)
//	{
//		m_x = rand() % WITDH;
//		m_y = rand() % HEIGHT;
//		if (m_x != 0 && m_x != HEIGHT - 1 && m_y != 0 && m_y != WITDH - 1 &&
//			(player.x != m_x && player.x != m_y) && (map[player.y][player.x] != WALL))
//		{
//			map[m_x][m_y] = TREASURE;
//		}
//		--TreausreNum;
//		if (TreausreNum < 0)
//		{
//			break;
//		}
//	}
//}