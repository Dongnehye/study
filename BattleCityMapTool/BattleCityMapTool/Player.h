#pragma once
#include <Windows.h>

class Player
{

	POINT point;
public:
	Player();
	virtual ~Player();

	void PositionMoveX(int x);
	void PositionMoveY(int y);

	POINT GetPosition();
};

