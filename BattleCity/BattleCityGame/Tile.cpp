#include "Tile.h"
#include <iostream>

using namespace std;


void Tile::CheckTankCollision(std::vector<Tank*>& VecTank)
{
	for (auto iter = VecTank.begin(); iter != VecTank.end(); ++iter)
	{
		IntersectRcetTank((*iter), Collision);
	}
}

void Tile::CheckBulletCollision(std::vector<Bullet*>& VecBullet)
{

	for (auto iter = VecBullet.begin(); iter != VecBullet.end(); ++iter)
	{
		IntersectRcetBullet((*iter), Collision);
	}
}

void Tile::IntersectRcetTank(Tank * tank, RECT Collision)
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

			}
			else if (rcInter.bottom == Collision.bottom)
			{
				tank->Collision.top += InterH;
				tank->Collision.bottom += InterH;
				tank->AddPositionY((float)InterH);
			}
		}
		else
		{
			if (rcInter.left == Collision.left)
			{
				tank->Collision.left -= InterW;
				tank->Collision.right -= InterW;
				tank->AddPositionX((float)-InterW);
			}
			else if (rcInter.right == Collision.right)
			{
				tank->Collision.left += InterW;
				tank->Collision.right += InterW;
				tank->AddPositionX((float)InterW);
			}
		}
	}
}

void Tile::IntersectRcetBullet(Bullet * bullet, RECT &Collision)
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


Tile::Tile()
{
}


Tile::Tile(HWND hWnd,POINT pt,int _BlockStyle, int _ChangeIndex, Bitmap * _Bitmap)
{
	HDC hdc = GetDC(hWnd);

	TileSize.cx = TILE_SIZE;
	TileSize.cy = TILE_SIZE;

	Position = pt;
	x = (float)pt.x * (float)TileSize.cx;
	y = (float)pt.y * (float)TileSize.cy;
	Model = nullptr;
	SetBlockStyle(_BlockStyle, _ChangeIndex);
	SetBitmap(_Bitmap);

	Collision = { (int)x, (int)y, (int)x + TileSize.cx, (int)y + TileSize.cy };
	
	ReleaseDC(hWnd, hdc);
}


Tile::~Tile()
{
	if (Model != nullptr)
		delete Model;
}
void Tile::SetBlockStyle(int _BlockStyle,int _ChangeIndex)
{
	ChangeIndex = _ChangeIndex;
	BlockStyle = _BlockStyle;
}

void Tile::SetBitmap(Bitmap * _bitmap)
{
	Model = _bitmap;
}
void Tile::Update(std::vector<Tank*> &VecTank, std::vector<Bullet*> &VecBullet)
{
	CheckTankCollision(VecTank);
	CheckBulletCollision(VecBullet);

	
}
int Tile::GetChangeIndex()
{
	return ChangeIndex;
}

int Tile::GetBlockStyle()
{
	return BlockStyle;
}

RECT Tile::GetCollision()
{
	return Collision;
}

void Tile::Draw(HDC hdc)
{
	Model->BufferDraw(hdc, (int)x, (int)y, TileSize);
	FrameRect(hdc, &Collision, NULL);
}