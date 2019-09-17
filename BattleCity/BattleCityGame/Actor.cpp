#include "Actor.h"
#include "Common.h"


Actor::Actor()
{
	TileSize.cx = TILE_SIZE;
	TileSize.cy = TILE_SIZE;
}


Actor::~Actor()
{
}
void Actor::Update(float fElapseTime)
{
}
void Actor::Draw(HDC hdc)
{
	Model->BufferDraw(hdc, x, y, TileSize);
	FrameRect(hdc, &Collision,NULL);
}
