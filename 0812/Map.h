#pragma once
#include <iostream>
#include <time.h>


#define WIDTH 30
#define HEIGHT 20

class Map
{
public:
	enum TILE
	{
		TILE_EMPTY,
		TILE_WALL,
		TILE_PLAYER,
		TILE_FOOD
	};
private:
	TILE map[HEIGHT][WIDTH];
	static int countFoodTime;
public:
	Map();
	~Map();
	void Init();
	void DrawMap();
	void UpdataFood();

	inline bool isTileWall(int x, int y)
	{
		if (map[y][x] == TILE_WALL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	inline void SetPlayer(int x, int y)
	{
		if (x != 0 && y != 0)
		{
			map[y][x] = TILE_PLAYER;
		}
	}
	inline void SetEMPTYPlayer(int x, int y)
	{
		if (x != 0 && y != 0)
		{
			map[y][x] = TILE_EMPTY;
		}
	}
	inline void SetFood(int x, int y)
	{
		map[y][x] = TILE_FOOD;
	}
	inline bool CheckFood(int x, int y)
	{
		if (map[y][x] == TILE_FOOD)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};