#include "MainTool.h"
#include <iostream>
#include <string>
#include <fstream>

MainTool * MainTool::m_sThis = nullptr;

using namespace std;

void MainTool::ChangeTile(Tile * tile, bool IsLeftClick)
{
	int Style = tile->GetBlockStyle();
	if (Style == BLOCK_EMPTY)
	{
		AddUndo(tile, STATE_INSERT);
		if(BlockStyle == BLOCK_BRICK)
			SetTIle(tile, &BlockBrick[BLOCKCHANGE_FULL], BlockStyle);
		else if(BlockStyle == BLOCK_SILVER)
			SetTIle(tile, &BlockSilver[BLOCKCHANGE_FULL], BlockStyle);
		else if (BlockStyle == BLOCK_WATER)
			SetTIle(tile, &BlockWater, BlockStyle);
		else if (BlockStyle == BLOCK_FOREST)
			SetTIle(tile, &BlockForest, BlockStyle);
		else if (BlockStyle == BLOCK_METAL)
			SetTIle(tile, &BlockMetal, BlockStyle);
		else if (BlockStyle == BLOCK_ENGLE)
			SetTIle(tile, &BlockEngle, BlockStyle);
	}
	else if (Style == BLOCK_BRICK || Style == BLOCK_SILVER)
	{
		if (IsLeftClick)
		{
			AddUndo(tile, STATE_UPDATE);
			tile->SetChangeIndex(1);
		}
		else
		{
			AddUndo(tile, STATE_UPDATE);
			tile->SetChangeIndex(-1);
		}
	}
}
void MainTool::ChangeTile(Tile * tile, int _BlockStyle, int ChangeIndex)
{

	if (_BlockStyle == BLOCK_BRICK)
		SetTIle(tile, &BlockBrick[ChangeIndex], _BlockStyle);
	else if (_BlockStyle == BLOCK_SILVER)
		SetTIle(tile, &BlockSilver[ChangeIndex], _BlockStyle);
	else if (_BlockStyle == BLOCK_WATER)
		SetTIle(tile, &BlockWater, _BlockStyle);
	else if (_BlockStyle == BLOCK_FOREST)
		SetTIle(tile, &BlockForest, _BlockStyle);
	else if (_BlockStyle == BLOCK_METAL)
		SetTIle(tile, &BlockMetal, _BlockStyle);
	else if (_BlockStyle == BLOCK_ENGLE)
		SetTIle(tile, &BlockEngle, _BlockStyle);

}
void MainTool::DeleteTile(Tile * tile)
{
	int Style = tile->GetBlockStyle();
	if (Style != BLOCK_EMPTY)
	{
		SetTIle(tile, nullptr, BLOCK_EMPTY);
	}
}
void MainTool::AllDeleteTile()
{
	for (int i = 0; i < MAPSIZE; ++i)
	{
		for (int j = 0; j < MAPSIZE; ++j)
		{

			DeleteTile(map[i][j]);
		}
	}

}
void MainTool::ChangeArrowTile(Tile * tile)
{



}

void MainTool::SetTIle(Tile *tile, Bitmap *bitmap, int BlockStyle)
{
	tile->SetBitmap(bitmap);
	tile->SetBlockStyle(BlockStyle);
}

void MainTool::ActiveUndo()
{
	if (!Undo.empty())
	{
		int State = Undo.top()->GetState();
		//Undo.top()->GetTile()->;
		//

		if (State == STATE_INSERT)
		{
			State = STATE_DELETE;
		}
		else if (State == STATE_DELETE)
		{
			State = STATE_INSERT;
		}
		else if (State == STATE_UPDATE)
		{
			State = STATE_UPDATE;
		}
		RollbackData * pNew = new RollbackData(Undo.top()->GetTile(), State);
		Redo.push(pNew);

		Undo.top()->Active();
		delete Undo.top();
		Undo.pop();
	}
}

void MainTool::ActiveRedo()
{
	if (!Redo.empty())
	{
		Redo.top()->Active();
		delete Redo.top();
		Redo.pop();
	}
}
MainTool::MainTool()
{
}


void MainTool::AddUndo(Tile * tile, int UndoState)
{
	RollbackData * pNew = new RollbackData(tile,UndoState);
	Undo.push(pNew);
}
void MainTool::AddRedo(RollbackData * _RollbackData)
{
	Redo.push(_RollbackData);
}

void MainTool::Init(HDC hdc)
{
	MemDC = CreateCompatibleDC(hdc);
	MemBitmap = CreateCompatibleBitmap(hdc, 1280, 720);
	MemOldBitmap = (HBITMAP)SelectObject(MemDC, MemBitmap);

	size.cx = 33;
	size.cy = 33;
	BlockStyle = BLOCK_BRICK;

	for (int i = 0 ; i < MAPSIZE; ++i)
	{
		for (int j = 0; j < MAPSIZE; ++j)
		{
			POINT pt = {i,j};
			map[i][j] = new Tile(pt,size, BlockBrick, BlockSilver);
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
	case 'Z':
		ActiveUndo();
		break;
	case 'X':
		ActiveRedo();
		break;
	}
}
void MainTool::MouseInput(LPARAM lParam, bool IsLeftClick)
{

	MousePoint.x = LOWORD(lParam);
	MousePoint.y = HIWORD(lParam);

	for (int i = 0; i < MAPSIZE; ++i)
	{
		for (int j = 0; j < MAPSIZE; ++j)
		{
			if (PtInRect(&map[i][j]->GetCollision(), MousePoint))
			{				
				ChangeTile(map[i][j], IsLeftClick);
			}
		}
	}
}
void MainTool::MouseMiddleInput(LPARAM lParam)
{
	MousePoint.x = LOWORD(lParam);
	MousePoint.y = HIWORD(lParam);

	for (int i = 0; i < MAPSIZE; ++i)
	{
		for (int j = 0; j < MAPSIZE; ++j)
		{
			if (PtInRect(&map[i][j]->GetCollision(), MousePoint))
			{
				AddUndo(map[i][j], STATE_DELETE);
				DeleteTile(map[i][j]);
			}
		}
	}
}
void MainTool::Update()
{

}

void MainTool::SetCurrentBlock(int _BlockStyle)
{
	BlockStyle = _BlockStyle;
}

void MainTool::Save(HWND hWnd)
{
	OPENFILENAME OFN;
	char str[300];
	char lpstrFile[MAX_PATH] = "";

	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = hWnd;
	OFN.lpstrFilter = "Every File(*.*)\0*.*\0Text File\0*.txt;*.doc\0";
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 256;
	OFN.lpstrInitialDir = "c:\\";
	if (GetOpenFileName(&OFN) != 0) {
		sprintf(str, "%s 파일을 선택했습니다.", OFN.lpstrFile);
		MessageBox(hWnd, str, "파일 열기 성공", MB_OK);
	}
	ofstream out(OFN.lpstrFile);

	if (out.is_open())
	{
		for (int i = 0; i < MAPSIZE; ++i)
		{
			for (int j = 0; j < MAPSIZE; ++j)
			{
				if (map[i][j]->GetBlockStyle() != BLOCK_EMPTY)
				{
					out << j << " " << i << endl;
					out << map[i][j]->GetBlockStyle() << endl;
					out << map[i][j]->GetChangeIndex() << endl;
				}
			}
		}
	}
}

void MainTool::Load(HWND hWnd)
{
	OPENFILENAME OFN;

	char str[256];
	char lpstrFile[MAX_PATH] = "";

	ZeroMemory(&OFN, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = hWnd;
	OFN.lpstrFilter = "Every File(*.*)\0*.*\0Text File(*.*)\0*.txt;*.ini\0";
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 256;
	OFN.lpstrInitialDir = "c:\\";

	if (GetOpenFileName(&OFN) != 0)
	{
		sprintf(str, "%s 파일을 선택했습니다.", OFN.lpstrFile);
		MessageBox(hWnd, str, "파일 열기 성공", MB_OK);
	}
	ifstream in(OFN.lpstrFile);
	string s;
	POINT mpt;
	int mChangeIndex = 0;
	int mBlockStyle = 0;

	if (!in.is_open())
	{
		MessageBox(hWnd, "ERROR", "파일을 찾을 수 없습니다.", MB_OK);
		return ;
	}
	else
	{
		AllDeleteTile();
		while (in)
		{
			in >> s;
			mpt.x = atoi(s.c_str());
			in >> s;
			mpt.y = atoi(s.c_str());
			in >> s;
			mBlockStyle = atoi(s.c_str());
			in >> s;
			mChangeIndex = atoi(s.c_str());

			ChangeTile(map[mpt.y][mpt.x], mBlockStyle, mChangeIndex);
		}
	}
}

MainTool::~MainTool()
{
	delete player;
}
