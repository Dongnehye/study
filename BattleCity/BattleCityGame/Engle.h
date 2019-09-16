#pragma once
#include "Tile.h"
class Engle :
	public Tile
{
	bool GameOver;
	virtual void IntersectRcetBullet(Bullet* bullet, RECT &Collision);

	void CheckBulletCollision(std::vector<Bullet*>& VecBullet);

	Engle();
public:
	Engle(HWND hWnd, POINT pt, int _BlockStyle, int _ChangeIndex, Bitmap * _Bitmap);
	virtual ~Engle();

	virtual void Update(std::vector<Tank*> &VecTank, std::vector<Bullet*> &VecBullet);

	virtual void Draw(HDC hdc);
};

