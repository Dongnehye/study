#include "Map.h"

using namespace std;

int Map::countFoodTime = 0;

Map::Map()
{
}


Map::~Map()
{
}

void Map::Init()
{
	memset(map, TILE_EMPTY, sizeof(map));

	for (int i = 0; i < WIDTH; ++i)
	{
		map[0][i] = TILE_WALL;
		map[HEIGHT - 1][i] = TILE_WALL;
	}
	for (int i = 0; i < HEIGHT - 1; ++i)
	{
		map[i][0] = TILE_WALL;
		map[i][WIDTH - 1] = TILE_WALL;
	}

	srand(time(NULL));
}

void Map::DrawMap()
{
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			if (map[i][j] == TILE_PLAYER)
			{
				cout << "¡á";
			}
			else if (map[i][j] == TILE_FOOD)
			{
				cout << "¡Ú";
			}
			else if (map[i][j] == TILE_WALL)
			{
				cout << "£À";
			}
			else if (map[i][j] == TILE_EMPTY)
			{
				cout << "  ";
			}
		}
		cout << endl;
	}
}

void Map::UpdataFood()
{
	int x = 0;
	int y = 0;

	x = rand() % WIDTH;
	y = rand() % HEIGHT;

	if (countFoodTime >= 30)
	{
		if (!isTileWall(x, y))
		{
			SetFood(x, y);
			countFoodTime = 0;
		}
	}
	else
	{
		++countFoodTime;
	}
}
