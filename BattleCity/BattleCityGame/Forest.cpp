#include "Forest.h"



Forest::Forest()
{
}
Forest::Forest(HWND hWnd, POINT pt, int _BlockStyle, int _ChangeIndex, Bitmap * _Bitmap)
	:Tile(hWnd, pt, _BlockStyle, _ChangeIndex, _Bitmap)
{

}

Forest::~Forest()
{
}

void Forest::Update(std::vector<Tank*>& VecTank, std::vector<Bullet*>& VecBullet)
{
}
