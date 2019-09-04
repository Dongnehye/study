#include "Actor.h"



Actor::Actor()
{
}

Actor::Actor(HDC hdc)
{
	pt.x = 100;
	pt.y = 100;

	Model.Init(hdc,"Circus\\player0.bmp");
}


Actor::~Actor()
{

}

void Actor::Draw(HDC hdc)
{
	Model.BufferDraw(hdc, pt.x, pt.y);
}