#include "MainTool.h"

MainTool * MainTool::m_sThis = nullptr;

void MainTool::SetTIle(Tile *tile, Bitmap *bitmap, int BlockStyle)
{
	tile->BitmapModel(bitmap);
	tile->SetBlockStyle(BlockStyle);
}

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

	for (int i = 0 ; i < MAPSIZE; ++i)
	{
		for (int j = 0; j < MAPSIZE; ++j)
		{
			POINT pt = {i,j};
			map[i][j] = new Tile(pt);
		}
	}

	Background.Init(hdc,"BattleCity\\back_black.bmp");
	BlockWater.Init(hdc, "BattleCity\\block07.bmp");
	BlockForest.Init(hdc, "BattleCity\\block06.bmp");
	BlockMetal.Init(hdc, "BattleCity\\block05.bmp");
	BlockEngle.Init(hdc, "BattleCity\\block13.bmp");

	BlockBrick[BLOCKCHANGE_FULL].Init(hdc, "BattleCity\\block00.bmp");
	BlockBrick[BLOCKCHANGE_RIGHT].Init(hdc, "BattleCity\\block04.bmp");
	BlockBrick[BLOCKCHANGE_BOTTOM].Init(hdc, "BattleCity\\block03.bmp");
	BlockBrick[BLOCKCHANGE_LEFT].Init(hdc, "BattleCity\\block02.bmp");
	BlockBrick[BLOCKCHANGE_UP].Init(hdc, "BattleCity\\block01.bmp");

	BlockSilver[BLOCKCHANGE_FULL].Init(hdc, "BattleCity\\block08.bmp");
	BlockSilver[BLOCKCHANGE_RIGHT].Init(hdc, "BattleCity\\block12.bmp");
	BlockSilver[BLOCKCHANGE_BOTTOM].Init(hdc, "BattleCity\\block11.bmp");
	BlockSilver[BLOCKCHANGE_LEFT].Init(hdc, "BattleCity\\block10.bmp");
	BlockSilver[BLOCKCHANGE_UP].Init(hdc, "BattleCity\\block09.bmp");

	CursorTank.Init(hdc, "BattleCity\\tank_up_00.bmp");

	player = new Player();

	SetTIle(map[5][11], &BlockBrick[BLOCKCHANGE_FULL], BLOCK_BRICK);
	SetTIle(map[5][12], &BlockBrick[BLOCKCHANGE_FULL], BLOCK_BRICK);
	SetTIle(map[7][11], &BlockBrick[BLOCKCHANGE_FULL], BLOCK_BRICK);
	SetTIle(map[7][12], &BlockBrick[BLOCKCHANGE_FULL], BLOCK_BRICK);
	SetTIle(map[6][11], &BlockBrick[BLOCKCHANGE_FULL], BLOCK_BRICK);
	SetTIle(map[6][12], &BlockEngle, BLOCK_ENGLE);
}

void MainTool::Draw(HDC hdc)
{
	Background.BufferDraw(MemDC, 0, 0);

	for (int i = 0; i < MAPSIZE; ++i)
	{
		for (int j = 0; j < MAPSIZE; ++j)
		{
			if(map[i][j]->GetBlockStyle() != BLOCK_EMPTY)
				map[i][j]->Draw(MemDC,size);
		}
	}

	BlockBrick[BLOCKCHANGE_FULL].BufferDraw(hdc, 600, 30, size);
	BlockSilver[BLOCKCHANGE_FULL].BufferDraw(hdc, 600, 90, size);
	BlockWater.BufferDraw(hdc, 600, 150, size);
	BlockForest.BufferDraw(hdc, 600, 210, size);
	BlockMetal.BufferDraw(hdc, 600, 270, size);

	CursorTank.BufferDraw(MemDC, size.cx * player->GetPosition().x, size.cy * player->GetPosition().y, size);
	
	BitBlt(hdc, 0, 0, MAPSIZE * size.cx, MAPSIZE * size.cy, MemDC, 0, 0, SRCCOPY);

}

void MainTool::Input(WPARAM wParam)
{
	switch (wParam) 
	{
	case VK_UP:
		player->PositionMoveY(-1);
		break;
	case VK_DOWN:
		player->PositionMoveY(1);
		break;
	case VK_LEFT:
		player->PositionMoveX(-1);
		break;
	case VK_RIGHT:
		player->PositionMoveX(1);
		break;
	case 'z':
		//Next
		break;
	case 'x':
		//Prev
		break;
	case 'c':
		//Delete
		break;
	}

}
void MainTool::Update()
{



}

MainTool::~MainTool()
{
	delete player;
}
