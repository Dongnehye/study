#include "Tile.h"
#include "MainTool.h"


Tile::Tile()
{
}


Tile::Tile(POINT pt, SIZE size, Bitmap _BlockBrick[], Bitmap _BlockSilver[])
{
	Position = pt;
	bitmap = nullptr;
	ChangeIndex = BLOCKCHANGE_FULL;
	BlockStyle = BLOCK_EMPTY;

	for (int i = 0; i < BLOCKSTYLE_END; ++i)
	{
		BlockBrick[i] = &_BlockBrick[i];
		BlockSilver[i] = &_BlockSilver[i];
	}

	Collision = { pt.x * size.cx, pt.y * size.cy,pt.x * size.cx + size.cx, pt.y * size.cy + size.cy };
}


Tile::~Tile()
{
}

void Tile::SetChangeIndex(int _ChangeIndex)
{
	ChangeIndex += _ChangeIndex;
	if (ChangeIndex >= BLOCKCHANGE_END)
		ChangeIndex = BLOCKCHANGE_FULL;
	else if (ChangeIndex < BLOCKCHANGE_FULL)
		ChangeIndex = BLOCKCHANGE_UP;

	if(BlockStyle == BLOCK_BRICK)
		SetBitmap(BlockBrick[ChangeIndex]);
	else if (BlockStyle == BLOCK_SILVER)
		SetBitmap(BlockSilver[ChangeIndex]);
}

void Tile::SetBlockStyle(int _BlockStyle)
{
	ChangeIndex = 0;
	BlockStyle = _BlockStyle;
}

void Tile::SetBitmap(Bitmap * _bitmap)
{
	bitmap = _bitmap;

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

void Tile::Draw(HDC hdc, SIZE size)
{
	bitmap->BufferDraw(hdc, size.cx * Position.x, size.cy * Position.y, size);

}
