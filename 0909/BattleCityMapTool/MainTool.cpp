#include "MainTool.h"

MainTool * MainTool::m_sThis = nullptr;

MainTool::MainTool()
{
}


void MainTool::Init(HDC hdc)
{
	MemDC = CreateCompatibleDC(hdc);
	MemBitmap = CreateCompatibleBitmap(hdc, 1280, 720);
	MemOldBitmap = (HBITMAP)SelectObject(MemDC, MemBitmap);

	size.cx = 33;
	size.cy = 33;

	Background.Init(hdc,"BattleCity\\back_black.bmp");
	BlockWater.Init(hdc, "BattleCity\\block07.bmp");
	BlockForest.Init(hdc, "BattleCity\\block06.bmp");
	BlockMetal.Init(hdc, "BattleCity\\block05.bmp");
	BlockEngle.Init(hdc, "BattleCity\\block13.bmp");

	BlockBrick[BLOCKCHANGE_RIGHT].Init(hdc, "BattleCity\\block04.bmp");
	BlockBrick[BLOCKCHANGE_BOTTOM].Init(hdc, "BattleCity\\block03.bmp");
	BlockBrick[BLOCKCHANGE_LEFT].Init(hdc, "BattleCity\\block02.bmp");
	BlockBrick[BLOCKCHANGE_UP].Init(hdc, "BattleCity\\block01.bmp");
	BlockBrick[BLOCKCHANGE_FULL].Init(hdc, "BattleCity\\block00.bmp");

	BlockSilver[BLOCKCHANGE_RIGHT].Init(hdc, "BattleCity\\block12.bmp");
	BlockSilver[BLOCKCHANGE_BOTTOM].Init(hdc, "BattleCity\\block11.bmp");
	BlockSilver[BLOCKCHANGE_LEFT].Init(hdc, "BattleCity\\block10.bmp");
	BlockSilver[BLOCKCHANGE_UP].Init(hdc, "BattleCity\\block09.bmp");
	BlockSilver[BLOCKCHANGE_FULL].Init(hdc, "BattleCity\\block08.bmp");

	CursorTank.Init(hdc, "BattleCity\\tank_up_00.bmp");

}

void MainTool::Draw(HDC hdc)
{

	Background.BufferDraw(MemDC, 0, 0);

	BlockBrick[BLOCKCHANGE_FULL].BufferDraw(MemDC, size.cx * 5, size.cy * 12, size);
	BlockBrick[BLOCKCHANGE_FULL].BufferDraw(MemDC, size.cx * 5, size.cy * 11, size);
	BlockBrick[BLOCKCHANGE_FULL].BufferDraw(MemDC, size.cx * 7, size.cy * 12, size);
	BlockBrick[BLOCKCHANGE_FULL].BufferDraw(MemDC, size.cx * 7, size.cy * 11, size);
	BlockBrick[BLOCKCHANGE_FULL].BufferDraw(MemDC, size.cx * 6, size.cy * 11, size);
	BlockEngle.BufferDraw(MemDC, size.cx * 6, size.cy * 12, size);

	CursorTank.BufferDraw(MemDC, size.cx * 6, size.cy * 6, size);

	BlockBrick[BLOCKCHANGE_FULL].BufferDraw(hdc, 600, 30, size);
	BlockSilver[BLOCKCHANGE_FULL].BufferDraw(hdc, 600, 90, size);
	BlockWater.BufferDraw(hdc, 600, 150, size);
	BlockForest.BufferDraw(hdc, 600, 210, size);
	BlockMetal.BufferDraw(hdc, 600, 270, size);

	BitBlt(hdc, 0, 0, MAPSIZE * size.cx, MAPSIZE * size.cy, MemDC, 0, 0, SRCCOPY);

}

MainTool::~MainTool()
{
}
