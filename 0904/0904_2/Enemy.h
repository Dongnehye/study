#pragma once
#include "Actor.h"
class Enemy :
	public Actor
{
protected:
	RECT Collision;
	RECT ScoreCollision;
	Bitmap Back;
	Bitmap front;

	bool Isfront;

	int Speed;
public:
	Enemy();
	Enemy(HDC hdc);
	virtual ~Enemy();
	virtual void Draw(HDC hdc, SIZE size);
	bool IsScrollStartOver();

	RECT GetCollision();
	RECT GetScoreCollision();

	void SetPositionX(int x);
	virtual void Update();
};