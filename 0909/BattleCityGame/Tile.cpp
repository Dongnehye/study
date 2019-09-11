#include "Tile.h"



Tile::Tile()
{
}


Tile::Tile(POINT pt, SIZE size, Bitmap BlockBrick[], Bitmap BlockSilver[])
{

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

	if (BlockStyle == BLOCK_BRICK)
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
	Model = _bitmap;

}
void Tile::Update()
{
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