#include "Bullet.h"
#include <iostream>

using namespace std;

Bullet::Bullet()
{
}


Bullet::Bullet(HWND hWnd, int _Arrow,float _x,float _y ,bool _IsPlayer)
{
	HDC hdc = GetDC(hWnd);

	Arrow = _Arrow;
	TileSize.cx = 8;
	TileSize.cy = 8;

	x = _x + TILE_SIZE / 2 - TileSize.cx / 2;
	y = _y + TILE_SIZE / 2 - TileSize.cy / 2;

	Speed = BULLETSPEED;
	AnimationCount = BOOM00;

	IsPlayer = _IsPlayer;
	IsBoom = false;

	BulletNormal[UP] = new Bitmap(hdc, "BattleCity\\missile_00.bmp");
	BulletNormal[DOWN] = new Bitmap(hdc, "BattleCity\\missile_01.bmp");
	BulletNormal[LEFT] = new Bitmap(hdc, "BattleCity\\missile_02.bmp");
	BulletNormal[RIGHT] = new Bitmap(hdc, "BattleCity\\missile_03.bmp");

	BulletBoom[BOOM00] = new Bitmap(hdc, "BattleCity\\explosion_00.bmp");
	BulletBoom[BOOM01] = new Bitmap(hdc, "BattleCity\\explosion_01.bmp");
	BulletBoom[BOOM02] = new Bitmap(hdc, "BattleCity\\explosion_02.bmp");

	Model = BulletNormal[Arrow];

	ReleaseDC(hWnd, hdc);
}

Bullet::~Bullet()
{
	delete BulletNormal[UP];
	delete BulletNormal[DOWN];
	delete BulletNormal[LEFT];
	delete BulletNormal[RIGHT];
	delete BulletBoom[BOOM00];
	delete BulletBoom[BOOM01];
	delete BulletBoom[BOOM02];
}

void Bullet::Move(float fElapseTime)
{
	if (Arrow == UP)
	{
		y += -(Speed * fElapseTime);
	}
	else if (Arrow == DOWN)
	{
		y += (Speed * fElapseTime);
	}
	else if (Arrow == LEFT)
	{
		x += -(Speed * fElapseTime);
	}
	else if (Arrow == RIGHT)
	{
		x += (Speed * fElapseTime);
	}
}

void Bullet::Boom(float fElapseTime)
{
	BoomAnimation(fElapseTime);

}

void Bullet::BoomAnimation(float fElapseTime)
{
	Model = BulletBoom[AnimationCount];

	if (AnimationCount == 2)
		AnimationCount = 0;
	else
		++AnimationCount;
}

bool Bullet::CheckStageEnd()
{
	if (x <= 0)
	{
		x = 0;
		return true;
	}
	else if (x > STAGE_SIZE - TileSize.cx)
	{
		x = STAGE_SIZE - TileSize.cx;
		return true;
	}
	if (y <= 0)
	{
		y = 0;
		return true;
	}
	else if (y > STAGE_SIZE - TileSize.cy)
	{
		y = STAGE_SIZE - TileSize.cy;
		return true;
	}
	return false;
}

void Bullet::IsBoomActive()
{
	IsBoom = true;
	//TileSize.cx = TILE_SIZE;
	//TileSize.cy = TILE_SIZE;

	//x = x - TILE_SIZE / 2 + 4;
	//y = y - TILE_SIZE / 2 + 4;
}

void Bullet::Update(float fElapseTime)
{
	if (IsBoom)
	{
		//Boom(fElapseTime);
	}
	else if (CheckStageEnd())
	{
		IsBoomActive();
	}
	else
	{
		Move(fElapseTime);
		Collision = { (int)x, (int)y,(int)x + TileSize.cx, (int)y + TileSize.cy };
	}
}