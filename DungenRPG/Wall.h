#pragma once
#include "Actor.h"
class Wall :
	public Actor
{
public:
	Wall();
	virtual ~Wall();
	virtual void printActor();
	bool isWall();
};