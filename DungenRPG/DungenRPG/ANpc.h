#pragma once
#include "Actor.h"
#include "GameManager.h"
class ANpc :
	public Actor
{
public:
	ANpc();
	~ANpc();
	int ntalk;

	virtual void reaction();
	virtual void printActor();
};