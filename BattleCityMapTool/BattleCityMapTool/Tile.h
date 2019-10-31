#pragma once
#include "Bitmap.h"
#include <Windows.h>

class Tile
{
	RECT Collision;

	Bitmap * bitmap;
	int ChangeIndex;
	int BlockStyle;

	POINT Position;

	Bitmap * BlockBrick[5];
	Bitmap * BlockSilver[5];

public:
	Tile();
	Tile(POINT pt, SIZE size, Bitmap BlockBrick[], Bitmap BlockSilver[]);
	virtual ~Tile();
	void SetChangeIndex(int ChangeIndex);
	void SetBlockStyle(int BlockStyle);
	void SetBitmap(Bitmap * bitmap);

	int GetChangeIndex();
	int GetBlockStyle();
	RECT GetCollision();
	void Draw(HDC hdc, SIZE size);
};