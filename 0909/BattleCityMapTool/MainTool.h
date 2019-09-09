#pragma once
#include "Tile.h"
#include "Player.h"
#include "Bitmap.h"
#include <Windows.h>

#define MAPSIZE 13

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

class MainTool
{
	static MainTool* m_sThis;

	HDC MemDC;
	HBITMAP MemBitmap;
	HBITMAP MemOldBitmap;	
	
	HDC TMemDC;
	HBITMAP TMemBitmap;
	HBITMAP TMemOldBitmap;

	Bitmap Background;
	Bitmap BlockBrick[BLOCKCHANGE_END];
	Bitmap BlockSilver[BLOCKCHANGE_END];
	Bitmap BlockWater;
	Bitmap BlockForest;
	Bitmap BlockMetal;

	Bitmap BlockEngle;

	Bitmap CursorTank;

	SIZE size;
	Player * player;

	Tile * map[MAPSIZE][MAPSIZE];
	void SetTIle(Tile *tile, Bitmap *bitmap, int BlockStyle);
	MainTool();
public:
	static MainTool* GetInstance()
	{
		if (m_sThis == nullptr)
		{
			m_sThis = new MainTool();
		}
		return m_sThis;
	}

	void Init(HDC hdc);
	void Draw(HDC hdc);
	void Input(WPARAM wParam);
	void Update();

	~MainTool();
};

