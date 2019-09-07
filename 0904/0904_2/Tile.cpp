#include "Tile.h"
#include <iostream>


Tile::Tile()
{
}

Tile::Tile(HDC hdc, const char * FileName,int x, int y, SIZE _size)
{
	pt.x = x;
	pt.y = y;
	Model.Init(hdc, FileName);
	size = _size;
	StrTile = nullptr;
}

Tile::Tile(HDC hdc, const char * FileName, int x, int y, SIZE _size, const char * String)
{
	pt.x = x;
	pt.y = y;
	Model.Init(hdc, FileName);
	size = _size;
	StrTile = new StringTile(hdc, x, y, String);
}

Tile::~Tile()
{
	if (StrTile != nullptr)
	{
		delete StrTile;
	}

}

void Tile::Draw(HDC hdc, SIZE size)
{
	Actor::Draw(hdc, size);

	if(StrTile != nullptr)
		StrTile->Draw(hdc);
}
