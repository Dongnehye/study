#include "Metal.h"



Metal::Metal()
{
}
Metal::Metal(HWND hWnd, POINT pt, int _BlockStyle, int _ChangeIndex, Bitmap * _Bitmap)
	:Tile(hWnd, pt, _BlockStyle, _ChangeIndex, _Bitmap)
{

}

Metal::~Metal()
{
}

void Metal::Update(std::vector<Tank*>& VecTank, std::vector<Bullet*>& VecBullet)
{
}
