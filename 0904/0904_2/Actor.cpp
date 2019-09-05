#include "Actor.h"

int Actor::g_Index = 0;

Actor::Actor()
{
	IndexId = g_Index;
	++g_Index;
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
