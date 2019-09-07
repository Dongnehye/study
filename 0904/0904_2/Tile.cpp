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
}

Tile::~Tile()
{
}