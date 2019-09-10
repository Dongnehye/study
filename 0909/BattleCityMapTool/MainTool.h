#pragma once
#include "RollbackData.h"
#include "Tile.h"
#include "Player.h"
#include "Bitmap.h"
#include <stack>
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

enum UNDOSTATE
{
	STATE_INSERT,
	STATE_DELETE,
	STATE_UPDATE,
	STATE_END
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

	POINT MousePoint;
	int BlockStyle;

	std::stack<RollbackData*> Undo;
	std::stack<RollbackData*> Redo;

	Tile * map[MAPSIZE][MAPSIZE];
	void ChangeTile(Tile *tile, bool IsLeftClick);
	void AllDeleteTile();
	void SetTIle(Tile *tile, Bitmap *bitmap, int BlockStyle);

	void ActiveUndo();
	void ActiveRedo();

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
	void DeleteTile(Tile * tile);
	void ChangeArrowTile(Tile *tile);
	void ChangeTile(Tile *tile, int BlockStyle, int ChangeIndex);
	void AddUndo(Tile * tile, int UndoState);
	void AddRedo(RollbackData * _RollbackData);

	void Init(HDC hdc);
	void Draw(HDC hdc);
	void Input(WPARAM wParam);
	void MouseInput(LPARAM lParam, bool IsLeftClick);
	void MouseMiddleInput(LPARAM lParam);
	void Update();
	void SetCurrentBlock(int BlockStyle);

	void Save(HWND hWnd);
	void Load(HWND hWnd);

	~MainTool();
};

