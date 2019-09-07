#pragma once
#include "Actor.h"
class Enemy :
	public Actor
{
	RECT Collision;
	Bitmap Back;
	Bitmap front;

	bool Isfront;

	int Speed;
public:
	Enemy();
	Enemy(HDC hdc);
	virtual ~Enemy();
	virtual void Draw(HDC hdc, SIZE size);

	void Move();
};