#pragma once
#include "Tile.h"

class RollbackData
{
	Tile * tile;
	int State;
	Bitmap * bitmap;
	int ChangeIndex;
	int BlockStyle;

	void RollbackInsert();
	void RollbackDelete();
	void RollbackUpdate();

public:
	RollbackData();
	RollbackData(Tile * tile, int _State);
	~RollbackData();

	Tile * GetTile();
	void Active();
	int GetState();
};

