#pragma once
#include "Tile.h"
class Forest :
	public Tile
{
public:
	Forest();
	Forest(HWND hWnd, POINT pt, int _BlockStyle, int _ChangeIndex, Bitmap * _Bitmap);
	virtual ~Forest();

	virtual void Update(std::vector<Tank*> &VecTank, std::vector<Bullet*> &VecBullet);
};

