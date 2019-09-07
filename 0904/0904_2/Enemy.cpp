#include "Enemy.h"

Enemy::Enemy()
{
	Collision = { 0,0,0,0 };

	pt.x = 400;
	pt.y = 100;

	size.cx = 25;
	size.cy = 130;

	Speed = 0;

	Model = Back;

	Isfront = false;
}
Enemy::Enemy(HDC hdc)
{
	Collision = {0,0,0,0};

	pt.x = 400;
	pt.y = 170;
	size.cx = 25;
	size.cy = 180;

	Speed = 0;

	Back.Init(hdc, "Circus\\enemy_1b.bmp");
	front.Init(hdc, "Circus\\enemy_1f.bmp");

	Model = Back;

	Isfront = false;
}


Enemy::~Enemy()
{
}

void Enemy::Draw(HDC hdc, SIZE size)
{
	if (!Isfront)
		Actor::Draw(hdc,size);
	else
		front.BufferDraw(hdc, pt.x, pt.y,size);
}

void Enemy::Move()
{
	//Collision.left = ;
	//Collision.top = ;
	//Collision.right = ;
	//Collision.bottom = ;

	pt.x -= 10;
	--IndexId;
}
