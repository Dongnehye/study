#pragma once
#include "Actor.h"
class Wall :
	public Actor
{
public:
	bool binvisual;
public:
	Wall();
	void Init(bool _binvisual);
	virtual ~Wall();
	virtual void printActor();
};