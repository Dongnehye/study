#pragma once
#include "Common.h"
#include "Tile.h"
#include "Player.h"
#include "Bitmap.h"
#include <Windows.h>
#include <chrono>
using namespace std;

#define FPS 60

enum BLOCKSTYLE
{
	BLOCK_EMPTY,
	BLOCK_BRICK,
	BLOCK_SILVER,
	BLOCK_WATER,
	BLOCK_FOREST,
	BLOCK_METAL,
	BLOCK_ENGLE,
	BLOCKSTYLE_END
};

enum BLOCKCHANGE
{
	BLOCKCHANGE_FULL,
	BLOCKCHANGE_RIGHT,
	BLOCKCHANGE_BOTTOM,
	BLOCKCHANGE_LEFT,
	BLOCKCHANGE_UP,
	BLOCKCHANGE_END
};

class MainGame
{
	HWND mhWnd;
	chrono::system_clock::time_point m_LastTime;
	float m_fElapseTime;

	HDC hMemDC[2];
	HBITMAP hBitmap[2];
	HBITMAP hOld[2];

	Bitmap * BlockBrick[BLOCKCHANGE_END];
	Bitmap * BlockSilver[BLOCKCHANGE_END];
	Bitmap * BlockWater;
	Bitmap * BlockForest;
	Bitmap * BlockMetal;
	Bitmap * BlockEngle;

	Player * player;

	Tile * map[MAP_SIZE][MAP_SIZE];

	int Score;
	int EnemyNumber;
	
	void ResourceLoad(HDC hdc);
	void LoadMap();

	MainGame();
public:
	MainGame(HWND hWnd);
	~MainGame();


	void OperateInput();
	void Update();
	void Render();
};

