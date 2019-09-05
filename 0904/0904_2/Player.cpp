#include "Player.h"
#include <math.h>
#define PI 3.1415f

void Player::StateIdle()
{
	IsRun = false;
	IsBackRun = false;
	Speed = 0;
	//IsJump = false;
	//IsAir = false;
	Animation(ANI_IDLE);
}


float DegreeToRadies(float degree)
{
	return (PI / 180) * degree;

}

POINT DrawCircls(int x, int y, int xR, int yR, float Angle)
{
	POINT pos;
	pos.x = cosf(DegreeToRadies(Angle)) * xR + x;
	pos.y = sinf(DegreeToRadies(Angle)) * yR + y;

	return pos;
}

void Player::CosJump()
{
	int jumpSpeed = 3;
	static int dt = 0;
	
	// 이거 수정 된 값 계속 더해서 바꿔야함.

	float Angle = jumpSpeed * dt;
	Animation(ANI_JUMP);
	pt = DrawCircls(pt.x, pt.y, 30, 3, Angle);

	++dt;
}

void Player::Animation(ANIMATION animation)
{
	if (animation == ANI_IDLE)
	{
		Model = Idle;
		TickCount = false;
	}
	else if (animation == ANI_RUN)
	{
		if (TickCount)
		{
			Model = Idle;
			TickCount = false;
		}
		else
		{
			Model = Run;
			TickCount = true;

		}
	}
	else if (animation == ANI_BACKRUN)
	{
		if (TickCount)
		{
			Model = Idle;
			TickCount = false;
		}
		else
		{
			Model = BACKRUN;
			TickCount = true;
		}
	}
	else if (animation == ANI_JUMP)
	{
		Model = Jump;
	}
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
}


Player::~Player()
{
}

void Player::ActiveMove(int x)
{
	if (x > 0)
	{
		Animation(ANI_RUN);
		IsRun = true;
	}
	else if (x < 0)
	{
		Animation(ANI_BACKRUN);
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
		CosJump();
		return ;
	}
	if (IsRun || IsBackRun)
		pt.x += Speed;
}