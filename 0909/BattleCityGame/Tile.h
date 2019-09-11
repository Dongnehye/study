#pragma once
#include "MainGame.h"
#include "Bitmap.h"
#include "Actor.h"
class Tile :
	public Actor
{
	// 여러갈래로 부서지는거.
	int ChangeIndex;
	int BlockStyle;

	Bitmap * BlockBrick[5];
	Bitmap * BlockSilver[5];

public:
	Tile();
	Tile(POINT pt, SIZE size, Bitmap BlockBrick[], Bitmap BlockSilver[]);
	virtual ~Tile();

	void SetChangeIndex(int ChangeIndex);
	void SetBlockStyle(int BlockStyle);
	void SetBitmap(Bitmap * bitmap);

	RECT GetCollision();
	int GetChangeIndex();
	int GetBlockStyle();

	virtual void Update();
};

