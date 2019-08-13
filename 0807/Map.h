#pragma once

#define WIDTH 20
#define HEIGHT 20

class Map
{
public:
	enum TILE
	{
		TILE_EMPTY,
		TILE_WALL,
		TILE_PLAYER
	};

private:
	TILE map[HEIGHT][WIDTH];

public:
	Map();
	~Map();

	int WallNum;
	int TreausreNum;

	void Init();
	void DrawMap();

	inline bool isTileWall(int x, int y)
	{
		if (map[y][x] == TILE_WALL)
			return true;
		else
			return false;
	}

	inline void SetPlayer(int x, int y)
	{
		map[y][x] = TILE_PLAYER;
	}

	inline void SetEmpty(int x, int y)
	{
		map[y][x] = TILE_EMPTY;
	}



};

