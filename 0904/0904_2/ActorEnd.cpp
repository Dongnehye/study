#include "ActorEnd.h"
#include "CommonHeader.h"


ActorEnd::ActorEnd()
{
}

ActorEnd::ActorEnd(HDC hdc)
{

	pt.x = STAGE_WITDH - 110;
	pt.y = 375;
	size.cx = 76;
	size.cy = 49;

	Model.Init(hdc, "Circus\\end.bmp");

	Collision = {pt.x,pt.y,pt.x + size.cx,pt.y+ size.cy };
}


ActorEnd::~ActorEnd()
{
}


RECT ActorEnd::GetCollision()
{
	return Collision;
}