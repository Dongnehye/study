#pragma once
#include "Tile.h"
class Metal :
	public Tile
{
	Metal();
public:
	Metal(HWND hWnd, POINT pt, int _BlockStyle, int _ChangeIndex, Bitmap * _Bitmap);
	virtual ~Metal();

	virtual void Update(std::vector<Tank*> &VecTank, std::vector<Bullet*> &VecBullet);
};