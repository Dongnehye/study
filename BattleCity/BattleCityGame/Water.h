#pragma once
#include "Tile.h"
class Water :
	public Tile
{
	Water();
public:
	Water(HWND hWnd, POINT pt, int _BlockStyle, int _ChangeIndex, Bitmap * _Bitmap);
	virtual ~Water();

	virtual void Update(std::vector<Tank*> &VecTank, std::vector<Bullet*> &VecBullet);
};

