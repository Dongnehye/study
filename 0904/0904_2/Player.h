#pragma once
#include "Actor.h"
class Player :
	public Actor
{
	Bitmap Idle;
	Bitmap Jump;
	Bitmap Run1;
	Bitmap Run2;
	Bitmap Win1;
	Bitmap Win2;
	Bitmap Die;

public:
	Player();
	Player(HDC hdc);
	virtual ~Player();

	void ActiveMove(int x);
	void ActiveJump();
};

