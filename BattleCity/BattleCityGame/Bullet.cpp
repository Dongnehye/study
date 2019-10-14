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
	TileSize.cx = BULLET_SIZE;
	TileSize.cy = BULLET_SIZE;

	x = _x + TILE_SIZE / 2 - TileSize.cx / 2;
	y = _y + TILE_SIZE / 2 - TileSize.cy / 2;

	Speed = BULLETSPEED;
	AnimationCount = BOOM00;
	BoomCount = 0.0f;

	IsPlayer = _IsPlayer;
	IsBoom = false;
	IsBoomEnd = false;

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
	for (int i = 0; i < ARROWEND; ++i)
	{
		delete BulletNormal[i];
	}
	for (int i = 0; i < BOOMEND; ++i)
	{
		delete BulletBoom[i];
	}
}
void Bullet::CheckBulletCollision(std::vector<Bullet*>& VecBullet)
{

	for (auto iter = VecBullet.begin(); iter != VecBullet.end(); ++iter)
	{
		if ((*iter)->GetIsPlayer() != IsPlayer)
			IntersectRcetBullet((*iter));
	}
}

void Bullet::IntersectRcetBullet(Bullet * bullet)
{
	RECT rcInter;
	if (IntersectRect(&rcInter, &bullet->Collision, &Collision))
	{
		int InterW = rcInter.right - rcInter.left;
		int InterH = rcInter.bottom - rcInter.top;

		if (InterW > InterH)
		{
			if (rcInter.top == Collision.top)
			{
				bullet->Collision.top += TILE_SIZE / 4;
			}
			else if (rcInter.bottom == Collision.bottom)
			{

				bullet->Collision.bottom -= TILE_SIZE / 4;
			}
		}
		else
		{
			if (rcInter.left == Collision.left)
			{
				bullet->Collision.left += TILE_SIZE / 4;
			}
			else if (rcInter.right == Collision.right)
			{
				bullet->Collision.right -= TILE_SIZE / 4;
			}
		}
		IsBoomActive();
	}
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
	BoomCount += fElapseTime;
	if (BoomCount < 0.2f)
		BoomAnimation(fElapseTime);
	else
		IsBoomEnd = true;
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
		x = (float)STAGE_SIZE - (float)TileSize.cx;
		return true;
	}
	if (y <= 0)
	{
		y = 0;
		return true;
	}
	else if (y > STAGE_SIZE - TileSize.cy)
	{
		y = (float)STAGE_SIZE - (float)TileSize.cy;
		return true;
	}
	return false;
}

void Bullet::IsBoomActive()
{
	IsBoom = true;
	x = x - TILE_SIZE / 4;
	y = y - TILE_SIZE / 4;
	TileSize.cx = TILE_SIZE;
	TileSize.cy = TILE_SIZE;
}

bool Bullet::GetIsPlayer()
{
	return IsPlayer;
}

bool Bullet::TimeOverBullet()
{
	return IsBoomEnd;
}

void Bullet::Update(float fElapseTime, std::vector<Bullet*> &VecBullet)
{
	if (IsBoom)
	{
		Boom(fElapseTime);
	}
	else if (CheckStageEnd())
	{
		IsBoomActive();
	}
	else
	{
		Move(fElapseTime);
		CheckBulletCollision(VecBullet);
		Collision = { (int)x, (int)y,(int)x + TileSize.cx, (int)y + TileSize.cy };
	}
}