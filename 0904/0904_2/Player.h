#pragma once
#include "Actor.h"
#include <vector>

enum ANIMATION
{
	ANI_IDLE,
	ANI_JUMP,
	ANI_RUN,
	ANI_BACKRUN,
	ANI_WIN,
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

	std::vector<Bitmap> RunAnimation;
	std::vector<Bitmap> BackRunAnimation;
	std::vector<Bitmap> WinAnimation;

	JUMPVECTOR JumpVector;
	POINT JumpMIddlePos;

	bool IsRun;
	bool IsBackRun;
	bool IsJump;
	bool IsAir;
	bool TickCount;
	int AnimaitonTickCount;

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