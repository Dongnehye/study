#pragma once

#include <iostream>

class Actor
{
public:
	int x;
	int y;
public:
	Actor();
	virtual ~Actor();

	virtual void printActor();
	void SetPosition(int _x, int _y);
	Actor * GetInstance();
};

