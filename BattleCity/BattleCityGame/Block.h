#pragma once
#include "Tile.h"

#define BlockBlick 5

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
	RECT TankCollisionLT;
	RECT TankCollisionRT;
	RECT TankCollisionLB;
	RECT TankCollisionRB;
	Bitmap * BlackTile;

	std::vector<POINT> BlackTilePoint;

	// 여러갈래로 부서지는거.

	Bitmap * BlockBrick[BLOCKCHANGE_END];

	void SetCollision();

	void CheckTankCollision(std::vector<Tank*> &VecTank);
	void CheckBulletCollision(std::vector<Bullet*> &VecBullet);

	void IntersectRcetTank(Tank * tank, RECT Collision);
	void IntersectRcetBullet(Bullet* bullet, RECT &Collision, RECT &TankCollision);

	Block();
public:
	Block(HWND hWnd, POINT pt, int _BlockStyle, int _ChangeIndex, Bitmap * _Bitmap);
	virtual ~Block();

	virtual void Update(std::vector<Tank*> &VecTank, std::vector<Bullet*> &VecBullet);

	virtual void Draw(HDC hdc);
};

