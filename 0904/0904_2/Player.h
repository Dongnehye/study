#pragma once
#include "Actor.h"

enum ANIMATION
{
	ANI_IDLE,
	ANI_JUMP,
	ANI_RUN,
	ANI_BACKRUN,
	ANI_WIN1,
	ANI_WIN2,
	ANI_DIE,
	ANI_END
};
enum JUMPVECTOR
{
	VECTOR_LEFT,
	VECTOR_MIDDLE,
	VECTOR_RIGHT
};

class Player :
	public Actor
{
	Bitmap Idle;
	Bitmap Jump;
	Bitmap Run;
	Bitmap BACKRUN;
	Bitmap Win1;
	Bitmap Win2;
	Bitmap Die;

	JUMPVECTOR JumpVector;
	POINT JumpMIddlePos;

	bool IsRun;
	bool IsBackRun;
	bool IsJump;
	bool IsAir;
	bool TickCount;

	int Speed;
	void CosJump();
	bool JumpOver();
	void Animation(ANIMATION animation);

public:
	Player();
	Player(HDC hdc);
	virtual ~Player();

	void StateIdle();
	void ActiveMove(int x);
	void ActiveJump();

	void Update();

};