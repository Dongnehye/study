#pragma once
#include "Actor.h"
class ActorEnd :
	public Actor
{
	RECT Collision;

public:
	ActorEnd();
	ActorEnd(HDC hdc);
	virtual ~ActorEnd();
	RECT GetCollision();
};

