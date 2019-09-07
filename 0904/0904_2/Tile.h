#pragma once
#include "Actor.h"
#include "StringTile.h"

class Tile :
	public Actor
{
	StringTile * StrTile;

public:
	Tile();
	Tile(HDC hdc, const char * FileName, int x, int y, SIZE _size);
	Tile(HDC hdc, const char * FileName, int x, int y, SIZE _size, const char * String);
	virtual ~Tile();

	virtual void Draw(HDC hdc, SIZE size);
};