#pragma once
#include "Tile.h"
class Sliver :
	public Tile
{
	Sliver();

	RECT CollisionLT;
	RECT CollisionRT;
	RECT CollisionLB;
	RECT CollisionRB;

	void SetCollision();
	virtual void CheckTankCollision(std::vector<Tank*> &VecTank);
	virtual void CheckBulletCollision(std::vector<Bullet*> &VecBullet);

	virtual void IntersectRcetTank(Tank * tank, RECT Collision);
	virtual void IntersectRcetBullet(Bullet* bullet, RECT &Collision);

public:
	Sliver(HWND hWnd, POINT pt, int _BlockStyle, int _ChangeIndex, Bitmap * _Bitmap);
	virtual ~Sliver();

	virtual void Update(std::vector<Tank*> &VecTank, std::vector<Bullet*> &VecBullet);

	virtual void Draw(HDC hdc);
};

