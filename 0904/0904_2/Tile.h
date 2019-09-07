#pragma once
#include "Actor.h"


class Tile :
	public Actor
{


public:
	Tile();
	Tile(HDC hdc, const char * FileName, int x, int y, SIZE _size);
	virtual ~Tile();
};