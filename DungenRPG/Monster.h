#pragma once
#include "MoveActor.h"
class Monster :
	public MoveActor
{

public:
	Monster();
	virtual ~Monster();

	virtual void Move();
	virtual void printActor();
};

