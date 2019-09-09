#pragma once
#include "Bitmap.h"
#include <Windows.h>

#define MAPSIZE 13

enum BLOCKSTYLE
{
	BLOCK_BRICK,
	BLOCK_SILVER,
	BLOCK_WATER,
	BLOCK_FOREST,
	BLOCK_METAL,
	BLOCKSTYLE_END
};

enum BLOCKCHANGE
{
	BLOCKCHANGE_RIGHT,
	BLOCKCHANGE_BOTTOM,
	BLOCKCHANGE_LEFT,
	BLOCKCHANGE_UP,
	BLOCKCHANGE_FULL,
	BLOCKCHANGE_END
};

class MainTool
{
	static MainTool* m_sThis;

	HDC MemDC;
	HBITMAP MemBitmap;
	HBITMAP MemOldBitmap;

	Bitmap Background;
	Bitmap BlockBrick[BLOCKCHANGE_END];
	Bitmap BlockSilver[BLOCKCHANGE_END];
	Bitmap BlockWater;
	Bitmap BlockForest;
	Bitmap BlockMetal;

	Bitmap BlockEngle;

	Bitmap CursorTank;

	SIZE size;

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
	void Update();

	~MainTool();
};

