#pragma once
#include "Bitmap.h"
#include "Tank.h"
#include "Bullet.h"
#include "Common.h"
#include <vector>

class Tile
{
protected:
	float x;
	float y;

	SIZE TileSize;
	RECT Collision;
	POINT Position;
	Bitmap * Model;

	// 여러갈래로 부서지는거.
	int ChangeIndex;
	int BlockStyle;

	virtual void CheckTankCollision(std::vector<Tank*> &VecTank);
	virtual void CheckBulletCollision(std::vector<Bullet*> &VecBullet);

	virtual void IntersectRcetTank(Tank * tank, RECT Collision);
	virtual void IntersectRcetBullet(Bullet* bullet, RECT &Collision);

	Tile();
public:
	Tile(HWND hWnd,POINT pt, int _BlockStyle, int _ChangeIndex, Bitmap * _Bitmap);
	virtual ~Tile();

	void SetBlockStyle(int _BlockStyle, int _ChangeIndex);
	void SetBitmap(Bitmap * bitmap);

	RECT GetCollision();
	int GetChangeIndex();
	int GetBlockStyle();

	virtual void Update(std::vector<Tank*> &VecTank, std::vector<Bullet*> &VecBullet);

	virtual void Draw(HDC hdc);
};