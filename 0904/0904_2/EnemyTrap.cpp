#include "EnemyTrap.h"
#include "CommonHeader.h"


EnemyTrap::EnemyTrap()
{
}
EnemyTrap::EnemyTrap(HDC hdc)
{

	Collision = { 0,0,0,0 };

	pt.x = STAGE_WITDH;
	pt.y = 375;
	size.cx = 50;
	size.cy = 50;

	Speed = 0;

	Back.Init(hdc, "Circus\\front.bmp");
	front.Init(hdc, "Circus\\front2.bmp");

	Model = Back;

	Isfront = false;
}

EnemyTrap::~EnemyTrap()
{
}

void EnemyTrap::Draw(HDC hdc, SIZE size)
{
	static int AnimaitionCount = 0;
	if (AnimaitionCount < 20)
	{
		Back.BufferDraw(hdc, pt.x, pt.y, size);
		++AnimaitionCount;
	}
	else if(AnimaitionCount < 40)
	{
		front.BufferDraw(hdc, pt.x, pt.y, size);
		++AnimaitionCount;
	}
	else
		AnimaitionCount = 0;
}

void EnemyTrap::Update()
{
	Collision = { pt.x + 20 ,pt.y + 20,pt.x + size.cx - 20 , pt.y + size.cy };
}