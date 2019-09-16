#pragma once
#include "Tile.h"
class Block :
	public Tile
{
protected:
	float x;
	float y;

	RECT CollisionLT;
	RECT CollisionRT;
	RECT CollisionLB;
	RECT CollisionRB;
	Bitmap * BlackTile;

	std::vector<POINT> BlackTilePoint;

	// 여러갈래로 부서지는거.

	Bitmap * BlockBrick[5];

	void SetCollision();

	void CheckTankCollision(std::vector<Tank*> &VecTank);
	void CheckBulletCollision(std::vector<Bullet*> &VecBullet);

	void IntersectRcetTank(Tank * tank, RECT Collision);
	void IntersectRcetBullet(Bullet* bullet, RECT &Collision);

	Block();
public:
	Block(HWND hWnd, POINT pt, int _BlockStyle, int _ChangeIndex, Bitmap * _Bitmap);
	virtual ~Block();

	virtual void Update(std::vector<Tank*> &VecTank, std::vector<Bullet*> &VecBullet);

	virtual void Draw(HDC hdc);
};

