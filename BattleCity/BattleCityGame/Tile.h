#pragma once
#include "Bitmap.h"
#include "Tank.h"
#include "Bullet.h"
#include <vector>

class Tile
{
	float x;
	float y;

	SIZE TileSize;
	RECT Collision;
	POINT Position;
	Bitmap * Model;

	// ���������� �μ����°�.
	int ChangeIndex;
	int BlockStyle;

	Bitmap * BlockBrick[5];
	Bitmap * BlockSilver[5];

	Tile();
public:
	Tile(POINT pt, int _BlockStyle, int _ChangeIndex, Bitmap * _Bitmap);
	virtual ~Tile();

	void SetBlockStyle(int _BlockStyle, int _ChangeIndex);
	void SetBitmap(Bitmap * bitmap);

	RECT GetCollision();
	int GetChangeIndex();
	int GetBlockStyle();

	void Update(std::vector<Tank*> &VecTank, std::vector<Bullet*> &VecBullet);
	virtual void Draw(HDC hdc);
};