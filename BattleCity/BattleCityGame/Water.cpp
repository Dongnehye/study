#include "Water.h"



Water::Water()
{
}
Water::Water(HWND hWnd, POINT pt, int _BlockStyle, int _ChangeIndex, Bitmap * _Bitmap)
	:Tile(hWnd, pt, _BlockStyle, _ChangeIndex, _Bitmap)
{

}

Water::~Water()
{
}

void Water::Update(std::vector<Tank*>& VecTank, std::vector<Bullet*>& VecBullet)
{
	CheckTankCollision(VecTank);
}
