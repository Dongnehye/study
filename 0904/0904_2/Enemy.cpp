#include "Enemy.h"
#include "CommonHeader.h"

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

	pt.x = STAGE_WITDH;
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
	{
		Back.BufferDraw(hdc, pt.x - size.cx / 2, pt.y, size);
		Isfront = true;
	}
	else
	{
		front.BufferDraw(hdc, pt.x + size.cx / 2, pt.y, size);
		Isfront = false;
	}
}

bool Enemy::IsScrollStartOver()
{
	if (pt.x < 0)
		return true;
	else
		return false;
}

RECT Enemy::GetCollision()
{
	return Collision;
}

RECT Enemy::GetScoreCollision()
{
	return ScoreCollision;
}

void Enemy::SetPositionX(int x)
{
	pt.x = x;
}

void Enemy::Update()
{
	pt.x -= 1;
	ScoreCollision = { pt.x + 7 ,pt.y + 10 ,pt.x + size.cx,pt.y + size.cy };
	Collision = { pt.x + 7 ,pt.y + size.cy - 10 ,pt.x + size.cx,pt.y + size.cy};
}
