#include "Actor.h"



Actor::Actor()
{
	TileSize.cx = 33;
	TileSize.cy = 33;
}


Actor::~Actor()
{
}

void Actor::Draw(HDC hdc)
{
	Model->BufferDraw(hdc, x, y, TileSize);
}
