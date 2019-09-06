#pragma once
#include "Actor.h"
class Enemy :
	public Actor
{
	Bitmap Back;
	Bitmap front;

	int Speed;
public:
	Enemy();
	Enemy(HDC hdc);
	virtual ~Enemy();
};