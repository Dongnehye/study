#include "Tile.h"
#include "Common.h"
#include <iostream>

using namespace std;


Tile::Tile()
{
}


Tile::Tile(POINT pt,int _BlockStyle, int _ChangeIndex, Bitmap * _Bitmap)
{
	TileSize.cx = TILE_SIZE;
	TileSize.cy = TILE_SIZE;

	Position = pt;
	x = (float)pt.x * (float)TileSize.cx;
	y = (float)pt.y * (float)TileSize.cy;
	Model = nullptr;
	SetBlockStyle(_BlockStyle, _ChangeIndex);
	SetBitmap(_Bitmap);

	Collision = { (int)x, (int)y, (int)x + TileSize.cx, (int)y + TileSize.cy};
}


Tile::~Tile()
{
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
	RECT rcInter;

	for (auto iter = VecTank.begin(); iter != VecTank.end(); ++iter)
	{
		if (IntersectRect(&rcInter, &(*iter)->Collision, &Collision))
		{
			int InterW = rcInter.right - rcInter.left;
			int InterH = rcInter.bottom - rcInter.top;

			if (InterW > InterH)
			{
				if (rcInter.top == Collision.top)
				{
					(*iter)->Collision.top -= InterH;
					(*iter)->Collision.bottom -= InterH;
					(*iter)->AddPositionY((float)-InterH);

				}
				else if (rcInter.bottom == Collision.bottom)
				{
					(*iter)->Collision.top += InterH;
					(*iter)->Collision.bottom += InterH;
					(*iter)->AddPositionY((float)InterH);
				}
			}
			else
			{
				if (rcInter.left == Collision.left)
				{
					(*iter)->Collision.left -= InterW;
					(*iter)->Collision.right -= InterW;
					(*iter)->AddPositionX((float)-InterW);
				}
				else if (rcInter.right == Collision.right)
				{
					(*iter)->Collision.left += InterW;
					(*iter)->Collision.right += InterW;
					(*iter)->AddPositionX((float)InterW);
				}
			}
		}
	}


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
