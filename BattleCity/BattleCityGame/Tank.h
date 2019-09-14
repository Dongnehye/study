#pragma once
#include "Actor.h"

enum TANKANIMATION
{
	IDLE,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Tank :
	public Actor
{
	int AnimationCount;
	void ApproximationTilePos(float &Number);
protected:
	int Arrow;
	int speed;

	Bitmap * Up[2];
	Bitmap * Down[2];
	Bitmap * Left[2];
	Bitmap * Right[2];

public:
	Tank();
	virtual ~Tank();

	void Move(float fElapseTime);
	void Fire();
	void MoveAnimation();

	void AddPositionX(float _x);

	void AddPositionY(float _y);

	virtual void Update() = 0;
};