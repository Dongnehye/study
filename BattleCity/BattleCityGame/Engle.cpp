#include "Engle.h"



void Engle::IntersectRcetBullet(Bullet * bullet, RECT & Collision)
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
	}
}

void Engle::CheckBulletCollision(std::vector<Bullet*>& VecBullet)
{

	for (auto iter = VecBullet.begin(); iter != VecBullet.end(); ++iter)
	{
		IntersectRcetBullet((*iter), Collision);
		GameOver = true;
	}
}

Engle::Engle()
{
}


Engle::Engle(HWND hWnd, POINT pt, int _BlockStyle, int _ChangeIndex, Bitmap * _Bitmap)
	:Tile(hWnd, pt, _BlockStyle, _ChangeIndex, _Bitmap)
{
	GameOver = false;
}

Engle::~Engle()
{
}

void Engle::Update(std::vector<Tank*>& VecTank, std::vector<Bullet*>& VecBullet)
{
	Tile::CheckTankCollision(VecTank);
	CheckBulletCollision(VecBullet);
}

void Engle::Draw(HDC hdc)
{
	Model->BufferDraw(hdc, (int)x, (int)y, TileSize);
	FrameRect(hdc, &Collision, NULL);
}
