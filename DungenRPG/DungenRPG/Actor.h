#pragma once

#include <iostream>

class Actor
{
public:
	int x;
	int y;
	bool bBlock;
public:
	Actor();
	virtual ~Actor();

	virtual void printActor();
	virtual void reaction();
	void SetPosition(int _x, int _y);
	Actor * GetInstance();
};

