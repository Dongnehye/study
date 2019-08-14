#pragma once
#include "Actor.h"
#include <string>

class AcotrStr :
	public Actor
{
public:
	std::string str;

public:
	AcotrStr();
	virtual ~AcotrStr();

	virtual void printActor();
};

