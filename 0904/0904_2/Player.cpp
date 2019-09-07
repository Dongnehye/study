#include "Player.h"
#include <math.h>
#define PI 3.1415f

void Player::StateIdle()
{
	IsRun = false;
	IsBackRun = false;
	Speed = 0;
	AnimaitonTickCount = 0;
}

void Player::CosJump()
{
	int JumpPosition = 0;
	static float bIsJumpInit = false;
	static float Angle = 180.0f;


	if (JumpVector == VECTOR_LEFT)
		JumpPosition = -100;
	else if (JumpVector == VECTOR_MIDDLE)
		JumpPosition = 0;
	else if (JumpVector == VECTOR_RIGHT)
		JumpPosition = 100;


	if (!bIsJumpInit)
	{
		JumpMIddlePos.x = pt.x + JumpPosition;
		JumpMIddlePos.y = pt.y;
		
		bIsJumpInit = true;
	}


	float Radian = Angle * PI / 180.f;

	pt.x = JumpMIddlePos.x + JumpPosition * cos(Radian);
	pt.y = JumpMIddlePos.y + 130 * sin(Radian);
	
	++Angle;
	IsAir = true;

	if (JumpOver())
	{
		bIsJumpInit = false;
		Angle = 180.0f;
	}

}

bool Player::JumpOver()
{
	if (pt.y > JumpMIddlePos.y)
	{
		IsAir = false;
		IsJump = false;
		pt.y = JumpMIddlePos.y;
		return true;
	}
	else
	{
		return false;
	}
}

void Player::Animation(ANIMATION animation)
{
	static int Count;

	if (animation == ANI_IDLE)
	{
		Model = Idle;
		TickCount = false;
	}
	else if (animation == ANI_RUN)
	{
		IsBackRun = false;
		Count = RunAnimation.size() - 1;
		Model = RunAnimation.at(AnimaitonTickCount);
	}
	else if (animation == ANI_BACKRUN)
	{
		IsRun = false;
		Count = BackRunAnimation.size() - 1;
		Model = BackRunAnimation.at(AnimaitonTickCount);
	}
	else if (animation == ANI_JUMP)
	{
		Model = Jump;
	}
	else if (animation == ANI_WIN)
	{
		Count = WinAnimation.size() - 1;
		Model = WinAnimation.at(AnimaitonTickCount);
	}
	else if (animation == ANI_DIE)
	{
		Model = Die;
	}
	if (AnimaitonTickCount >= Count)
		AnimaitonTickCount = 0;
	else
		++AnimaitonTickCount;
}

Player::Player()
{

}

Player::Player(HDC hdc)
{
	pt.x = 100;
	pt.y = 345;
	IndexId = 0;

	size.cx = 67;
	size.cy = 80;

	Speed = 0;

	Idle.Init(hdc,"Circus\\player0.bmp");
	Jump.Init(hdc, "Circus\\player2.bmp");
	Run.Init(hdc,"Circus\\player2.bmp");
	BACKRUN.Init(hdc,"Circus\\player1.bmp");
	Win1.Init(hdc,"Circus\\win.bmp");
	Win2.Init(hdc,"Circus\\win2.bmp");
	Die.Init(hdc,"Circus\\die.bmp");

	Model = Idle;

	IsRun		= false;
	IsBackRun	= false;
	IsJump		= false;
	IsAir		= false;
	TickCount	= false;

	RunAnimation.push_back(Run);
	RunAnimation.push_back(BACKRUN);
	RunAnimation.push_back(Idle);

	BackRunAnimation.push_back(BACKRUN);
	BackRunAnimation.push_back(Idle);

	WinAnimation.push_back(Win1);
	WinAnimation.push_back(Win2);
	AnimaitonTickCount = 0;
}


Player::~Player()
{
}

void Player::ActiveMove(int x)
{
	if (x > 0)
	{
		IsRun = true;
	}
	else if (x < 0)
	{
		IsBackRun = true;
	}
	Speed = x;
}

void Player::ActiveJump()
{
	if (IsBackRun)
	{
		JumpVector = VECTOR_LEFT;
	}
	else if (IsRun)
	{
		JumpVector = VECTOR_RIGHT;
	}
	else
	{
		JumpVector = VECTOR_MIDDLE;
	}

	IsJump = true;
}

void Player::Update()
{
	if (IsJump)
	{
		Animation(ANI_JUMP);
		CosJump();
	}
	else if (IsRun)
	{
		Animation(ANI_RUN);
		pt.x += Speed;
	}
	else if (IsBackRun)
	{
		Animation(ANI_BACKRUN);
		pt.x += Speed;
	}
	else
	{
		StateIdle();
		Animation(ANI_IDLE);
	}
		
}