#pragma once
#include "Actor.h"
class Tank :
	public Actor
{
public:
	Tank();
	virtual ~Tank();

	void Move();
	void Fire();

	virtual void Update() = 0;
};