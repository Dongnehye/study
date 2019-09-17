#include "Block.h"
#include "Common.h"


Block::Block()
{
}


Block::~Block()
{
}

void Block::SetCollision()
{
	if (ChangeIndex == BLOCKCHANGE_FULL)
	{
		CollisionLT = { (int)x, (int)y, (int)x + TileSize.cx / 2, (int)y + TileSize.cy / 2 };
		CollisionRT = { (int)x + TileSize.cx / 2, (int)y, (int)x + TileSize.cx, (int)y + TileSize.cy / 2 };
		CollisionLB = { (int)x, (int)y + TileSize.cy / 2, (int)x + TileSize.cx / 2, (int)y + TileSize.cy };
		CollisionRB = { (int)x + TileSize.cx / 2, (int)y + TileSize.cy / 2, (int)x + TileSize.cx, (int)y + TileSize.cy };
	}
	else if (ChangeIndex == BLOCKCHANGE_RIGHT)
	{
		CollisionLT = { 0, 0, 0, 0 };
		CollisionRT = { (int)x + TileSize.cx / 2, (int)y, (int)x + TileSize.cx, (int)y + TileSize.cy / 2 };
		CollisionLB = { 0, 0, 0, 0 };
		CollisionRB = { (int)x + TileSize.cx / 2, (int)y + TileSize.cy / 2, (int)x + TileSize.cx, (int)y + TileSize.cy };
	}
	else if (ChangeIndex == BLOCKCHANGE_BOTTOM)
	{
		CollisionLT = { 0, 0, 0, 0 };
		CollisionRT = { 0, 0, 0, 0 };
		CollisionLB = { (int)x, (int)y + TileSize.cy / 2, (int)x + TileSize.cx / 2, (int)y + TileSize.cy };
		CollisionRB = { (int)x + TileSize.cx / 2, (int)y + TileSize.cy / 2, (int)x + TileSize.cx, (int)y + TileSize.cy };
	}
	else if (ChangeIndex == BLOCKCHANGE_LEFT)
	{
		CollisionLT = { (int)x, (int)y, (int)x + TileSize.cx / 2, (int)y + TileSize.cy / 2 };
		CollisionRT = { 0, 0, 0, 0 };
		CollisionLB = { (int)x, (int)y + TileSize.cy / 2, (int)x + TileSize.cx / 2, (int)y + TileSize.cy };
		CollisionRB = { 0, 0, 0, 0 };
	}
	else if (ChangeIndex == BLOCKCHANGE_UP)
	{
		CollisionLT = { (int)x, (int)y, (int)x + TileSize.cx / 2, (int)y + TileSize.cy / 2 };
		CollisionRT = { (int)x + TileSize.cx / 2, (int)y, (int)x + TileSize.cx, (int)y + TileSize.cy / 2 };
		CollisionLB = { 0, 0, 0, 0 };
		CollisionRB = { 0, 0, 0, 0 };
	}
}

void Block::CheckTankCollision(std::vector<Tank*>& VecTank)
{
	for (auto iter = VecTank.begin(); iter != VecTank.end(); ++iter)
	{
		IntersectRcetTank((*iter), CollisionLT);
		IntersectRcetTank((*iter), CollisionRT);
		IntersectRcetTank((*iter), CollisionLB);
		IntersectRcetTank((*iter), CollisionRB);
	}
}

void Block::CheckBulletCollision(std::vector<Bullet*>& VecBullet)
{

	for (auto iter = VecBullet.begin(); iter != VecBullet.end(); ++iter)
	{
		IntersectRcetBullet((*iter), CollisionLT);
		IntersectRcetBullet((*iter), CollisionRT);
		IntersectRcetBullet((*iter), CollisionLB);
		IntersectRcetBullet((*iter), CollisionRB);
	}
}

void Block::IntersectRcetTank(Tank * tank, RECT Collision)
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

void Block::IntersectRcetBullet(Bullet * bullet, RECT &Collision)
{
	RECT rcInter;
	if (IntersectRect(&rcInter, &bullet->Collision, &Collision))
	{
		POINT pt;
		int InterW = rcInter.right - rcInter.left;
		int InterH = rcInter.bottom - rcInter.top;

		if (InterW > InterH)
		{
			if (rcInter.top == Collision.top)
			{
				pt.y = Collision.top;
				if (rcInter.left == Collision.left)
				{
					pt.x = Collision.left;
					BlackTilePoint.push_back(pt);
					pt.x = Collision.left + TILE_SIZE / 4;
					BlackTilePoint.push_back(pt);
				}
				else if (rcInter.right == Collision.right)
				{
					pt.x = Collision.right - TILE_SIZE / 4;
					BlackTilePoint.push_back(pt);
					pt.x = Collision.right - TILE_SIZE / 2;
					BlackTilePoint.push_back(pt);
				}
				Collision.top += TILE_SIZE / 4;
			}
			else if (rcInter.bottom == Collision.bottom)
			{
				pt.y = Collision.bottom - TILE_SIZE / 4;
				if (rcInter.left == Collision.left)
				{
					pt.x = Collision.left;
					BlackTilePoint.push_back(pt);
					pt.x = Collision.left + TILE_SIZE / 4;
					BlackTilePoint.push_back(pt);
				}
				else if (rcInter.right == Collision.right)
				{
					pt.x = Collision.right - TILE_SIZE / 4;
					BlackTilePoint.push_back(pt);
					pt.x = Collision.right - TILE_SIZE / 2;
					BlackTilePoint.push_back(pt);
				}
				Collision.bottom -= TILE_SIZE / 4;
			}
		}
		else
		{
			if (rcInter.left == Collision.left)
			{
				pt.x = Collision.left;
				if (rcInter.top == Collision.top)
				{
					pt.y = Collision.top;
					BlackTilePoint.push_back(pt);
					pt.y = Collision.top + TILE_SIZE / 4;
					BlackTilePoint.push_back(pt);
				}
				else if (rcInter.bottom == Collision.bottom)
				{
					pt.y = Collision.bottom - TILE_SIZE / 4;
					BlackTilePoint.push_back(pt);
					pt.y = Collision.bottom - TILE_SIZE / 2;
					BlackTilePoint.push_back(pt);
				}
				Collision.left += TILE_SIZE / 4;
			}
			else if (rcInter.right == Collision.right)
			{
				pt.x = Collision.right - TILE_SIZE / 4;
				if (rcInter.top == Collision.top)
				{
					pt.y = Collision.top;
					BlackTilePoint.push_back(pt);
					pt.y = Collision.top + TILE_SIZE / 4;
					BlackTilePoint.push_back(pt);
				}
				else if (rcInter.bottom == Collision.bottom)
				{
					pt.y = Collision.bottom - TILE_SIZE / 4;
					BlackTilePoint.push_back(pt);
					pt.y = Collision.bottom - TILE_SIZE / 2;
					BlackTilePoint.push_back(pt);
				}
				Collision.right -= TILE_SIZE / 4;
			}
		}
		bullet->IsBoomActive();
	}
}

Block::Block(HWND hWnd, POINT pt, int _BlockStyle, int _ChangeIndex, Bitmap * _Bitmap)
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

	SetCollision();
	BlackTile = new Bitmap(hdc, "BattleCity\\BlackTile.bmp");

	ReleaseDC(hWnd, hdc);
}

void Block::Update(std::vector<Tank*> &VecTank, std::vector<Bullet*> &VecBullet)
{
	CheckTankCollision(VecTank);
	CheckBulletCollision(VecBullet);
}

void Block::Draw(HDC hdc)
{
	Model->BufferDraw(hdc, (int)x, (int)y, TileSize);
	FrameRect(hdc, &CollisionLT, NULL);
	FrameRect(hdc, &CollisionRT, NULL);
	FrameRect(hdc, &CollisionLB, NULL);
	FrameRect(hdc, &CollisionRB, NULL);

	for (auto iter = BlackTilePoint.begin(); iter != BlackTilePoint.end(); ++iter)
	{
		BlackTile->BufferDraw(hdc, (*iter).x, (*iter).y);
	}
}
