#include "Tank.h"
#include "Common.h"
#include <iostream>
#include <math.h>

using namespace std;

void Tank::ApproximationTilePos(float & Number)
{
	float HalfTileSize = TILE_SIZE / 2;
	float DiffNumber = 0;
	float DiffMin = STAGE_SIZE;
	int MinNum = 0;

	for (int i = 0; i < MAP_SIZE * 2; ++i)
	{
		DiffNumber = Number - HalfTileSize * i;
		if (DiffMin > abs(DiffNumber))
		{
			DiffMin = DiffNumber;
			MinNum = i;
		}
	}

	Number = HalfTileSize * MinNum;
}

Tank::Tank()
{
	AnimationCount = 0;
	FireColdown = 0;
}


Tank::~Tank()
{
	delete Up[0];
	delete Up[1];
	delete Down[0];
	delete Down[1];
	delete Left[0];
	delete Left[1];
	delete Right[0];
	delete Right[1];
	Model = nullptr;
}

void Tank::Move(float fElapseTime)
{
	if (Arrow == UP)
		AddPositionX(-(speed * fElapseTime));
	else if (Arrow == DOWN)
		AddPositionY(-(speed * fElapseTime));
	else if (Arrow == LEFT)
		AddPositionX(speed * fElapseTime);
	else if (Arrow == RIGHT)
		AddPositionY(speed * fElapseTime);
}

void Tank::Fire(HWND hWnd, std::vector<Bullet*> &VecBullet)
{
	if (FireColdown <= 0)
	{
		Bullet * bullet = new Bullet(hWnd,Arrow,x,y,IsPlayer);
		VecBullet.push_back(bullet);
		FireColdown = 5;
	}
}

void Tank::Update(float fElapseTime)
{
	//if (sec.count() < 1000)
	//{
	//	return;
	//}
	if (FireColdown > 0)
		--FireColdown;

}

void Tank::MoveAnimation()
{
	if (Arrow == UP)
	{
		Model = Up[AnimationCount];
	}
	else if (Arrow == DOWN)
	{
		Model = Down[AnimationCount];
	}
	else if (Arrow == LEFT)
	{
		Model = Left[AnimationCount];
	}
	else if (Arrow == RIGHT)
	{
		Model = Right[AnimationCount];
	}
	if (AnimationCount == 0)
		AnimationCount = 1;
	else
		AnimationCount = 0;

}
void Tank::AddPositionX(float _x)
{
	if (Arrow == UP || Arrow == DOWN)
	{
		ApproximationTilePos(y);
	}

	if (_x > 0)
		Arrow = RIGHT;
	else
		Arrow = LEFT;

	x += _x;
	if (x <= 0)
		x = 0;
	else if (x > STAGE_SIZE - TILE_SIZE)
		x = STAGE_SIZE - TILE_SIZE;
}

void Tank::AddPositionY(float _y)
{
	if (Arrow == LEFT || Arrow == RIGHT)
	{
		ApproximationTilePos(x);
	}

	if (_y > 0)
		Arrow = DOWN;
	else 
		Arrow = UP;

	y += _y;
	if (y <= 0)
		y = 0;
	else if (y > STAGE_SIZE - TILE_SIZE)
		y = STAGE_SIZE - TILE_SIZE;
}