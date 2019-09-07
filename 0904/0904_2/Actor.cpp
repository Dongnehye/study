#include "Actor.h"

Actor::Actor()
{
}

Actor::Actor(HDC hdc)
{

}


Actor::~Actor()
{

}

void Actor::Draw(HDC hdc)
{
	Model.BufferDraw(hdc, pt.x, pt.y);
}
void Actor::Draw(HDC hdc, SIZE size)
{
	Model.BufferDraw(hdc, pt.x, pt.y, size);
}

POINT Actor::GetPoint()
{
	return pt;
}

SIZE Actor::GetSize()
{
	return size;
}

void Actor::SetIndexId(int Id)
{
	IndexId = Id;
}
