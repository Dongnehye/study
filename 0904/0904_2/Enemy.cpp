#include "Enemy.h"



Enemy::Enemy()
{
}
Enemy::Enemy(HDC hdc)
{
	pt.x = 400;
	pt.y = 100;
	IndexId = 0;

	size.cx = 67;
	size.cy = 80;

	Speed = 0;

	Back.Init(hdc, "Circus\\enemy_1b.bmp");
	front.Init(hdc, "Circus\\enemy_1f.bmp");

	Model = Back;
}


Enemy::~Enemy()
{
}
