#include "Tank.h"
#include "Common.h"
#include <iostream>
#include <math.h>

using namespace std;

void Tank::CheckTankCollision(std::vector<Tank*>& VecTank)
{
	for (auto iter = VecTank.begin(); iter != VecTank.end(); ++iter)
	{
		if((*iter) != this)
			IntersectRcetTank((*iter));
	}
}

void Tank::CheckBulletCollision(std::vector<Bullet*>& VecBullet)
{

	for (auto iter = VecBullet.begin(); iter != VecBullet.end(); ++iter)
	{
		if((*iter)->GetIsPlayer() != IsPlayer )
			IntersectRcetBullet((*iter));
	}
}

void Tank::IntersectRcetTank(Tank * tank)
{
	RECT rcInter;
	if (IntersectRect(&rcInter, &tank->Collision, &Collision))
	{
		int InterW = rcInter.right - rcInter.left;
		int InterH = rcInter.bottom - rcInter.top;

		if (InterW > InterH)
		{
			if (rcInter.top == Collision.top)
			{
				tank->Collision.top -= InterH;
				tank->Collision.bottom -= InterH;
				tank->AddPositionY((float)-InterH);
				AddPositionY((float)InterH);

			}
			else if (rcInter.bottom == Collision.bottom)
			{
				tank->Collision.top += InterH;
				tank->Collision.bottom += InterH;
				tank->AddPositionY((float)InterH);
				AddPositionY((float)-InterH);
			}
		}
		else
		{
			if (rcInter.left == Collision.left)
			{
				tank->Collision.left -= InterW;
				tank->Collision.right -= InterW;
				tank->AddPositionX((float)-InterW);
				AddPositionX((float)InterW);
			}
			else if (rcInter.right == Collision.right)
			{
				tank->Collision.left += InterW;
				tank->Collision.right += InterW;
				tank->AddPositionX((float)InterW);
				AddPositionX((float)-InterW);
			}
		}
	}
}

void Tank::IntersectRcetBullet(Bullet * bullet)
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
		bullet->IsBoomActive();
		IsBoom = true;
	}
}

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

void Tank::BoomAnimation(float ElapseTime)
{
	BoomAnimCount += ElapseTime;
	Collision = { 0, 0, 0, 0 };
	if (BoomAnimCount > 1.8f)
	{
		IsBoomEnd = true;
	}
	else if (BoomAnimCount > 1.5f)
	{
		Model = TankBoom[TANKBOOM04];
		TileSize.cx = 42;
		TileSize.cy = 38;
	}
	else if (BoomAnimCount > 1.0f)
	{
		Model = TankBoom[TANKBOOM03];
		TileSize.cx = 42;
		TileSize.cy = 38;
	}
	else if (BoomAnimCount > 0.7f)
	{
		Model = TankBoom[TANKBOOM02];
	}
	else if (BoomAnimCount > 0.3f)
	{
		Model = TankBoom[TANKBOOM01];
	}
	else if (BoomAnimCount > 0.1f)
	{
		Model = TankBoom[TANKBOOM00];
	}
}

Tank::Tank()
{
	AnimationCount = 0;
	FireColdown = 0;
	Second = 0;
	IsBoom = false;
	IsBoomEnd = false;
	IsTankDie = false;
	BoomAnimCount = 0;
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

	for (int i = 0; i < TANKBOOMEND; ++i)
	{
		delete TankBoom[i];
	}
}

void Tank::Fire(HWND hWnd, std::vector<Bullet*> &VecBullet)
{
	if (IsBoom)
	{
		return;
	}
	if (FireColdown <= 0)
	{
		Bullet * bullet = new Bullet(hWnd,Arrow,x, y,IsPlayer);
		VecBullet.push_back(bullet);
		FireColdown = 2;
	}
}

void Tank::Update(float fElapseTime, std::vector<Bullet*> &VecBullet, std::vector<Tank*> &VecTank)
{
	Second += fElapseTime;
	if (FireColdown > 0 && Second > 1)
	{
		--FireColdown;
		Second = 0;
	
	}

	CheckTankCollision(VecTank);
	CheckBulletCollision(VecBullet);
}

void Tank::Update(float fElapseTime,HWND hWnd, std::vector<Bullet*> &VecBullet, std::vector<Tank*> &VecTank)
{
	Update(fElapseTime, VecBullet, VecTank);
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

void Tank::Move(float fElapseTime)
{
	if (Arrow == UP)
		AddPositionY(-(speed * fElapseTime));
	else if (Arrow == DOWN)
		AddPositionY(speed * fElapseTime);
	else if (Arrow == LEFT)
		AddPositionX(-(speed * fElapseTime));
	else if (Arrow == RIGHT)
		AddPositionX(speed * fElapseTime);
}

void Tank::AddPositionX(float _x)
{
	if (IsBoom)
	{
		return;
	}

	if (PreArrow == UP || PreArrow == DOWN)
	{
		ApproximationTilePos(y);
	}


	x += _x;
	if (x <= 0)
		x = 0;
	else if (x > STAGE_SIZE - TILE_SIZE)
		x = STAGE_SIZE - TILE_SIZE;
	PreArrow = Arrow;
}

void Tank::AddPositionY(float _y)
{
	if (IsBoom)
	{
		return;
	}
	if (PreArrow == LEFT || PreArrow == RIGHT)
	{
		ApproximationTilePos(x);
	}


	y += _y;
	if (y <= 0)
		y = 0;
	else if (y > STAGE_SIZE - TILE_SIZE)
		y = STAGE_SIZE - TILE_SIZE;

	PreArrow = Arrow;
}

bool Tank::GetTankDIe()
{
	return IsTankDie;
}
