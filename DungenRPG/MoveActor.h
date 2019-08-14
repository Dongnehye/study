#pragma once
#include "Actor.h"
class MoveActor :
	public Actor
{
public:
	int hp;
	int mp;
	int atk;
	int def;
	int level;

public:
	MoveActor();
	virtual ~MoveActor();

	virtual void Move() = 0;
	//virtual void InputButton() = 0;
};