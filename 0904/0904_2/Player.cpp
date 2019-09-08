#include "Player.h"
#include "CommonHeader.h"
#include <math.h>
#include <algorithm>

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
	int JumpSpeed = 2;
	static float bIsJumpInit = false;
	static float Angle = 180.0f;


	if (JumpVector == VECTOR_LEFT)
		JumpPosition = -80;
	else if (JumpVector == VECTOR_MIDDLE)
		JumpPosition = 0;
	else if (JumpVector == VECTOR_RIGHT)
		JumpPosition = 80;


	if (!bIsJumpInit)
	{
		JumpMIddlePos.x = pt.x + JumpPosition;
		JumpMIddlePos.y = pt.y;
		
		bIsJumpInit = true;
	}


	float Radian = Angle * PI / 180.f;

	pt.x = JumpMIddlePos.x + JumpPosition * cos(Radian);
	pt.y = JumpMIddlePos.y + 130 * sin(Radian);
	
	Angle += JumpSpeed;
	IsAir = true;

	if (JumpOver())
	{
		bIsJumpInit = false;
		Angle = 180.0f;
		if (bAddScore)
		{
			Score += 100;
			bAddScore = false;
		}
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
		Count = RunAnimation.size() - 1;
		Model = RunAnimation.at(AnimaitonTickCount);
	}
	else if (animation == ANI_BACKRUN)
	{
		Count = BackRunAnimation.size() - 1;
		Model = BackRunAnimation.at(AnimaitonTickCount);
	}
	else if (animation == ANI_JUMP)
	{
		Model = Jump;
		AnimaitonTickCount = 0;
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
	Life = MAXLIFE;

	pt.x = 100;
	pt.y = 335;

	size.cx = 67;
	size.cy = 90;

	Speed = 0;
	Score = 0;
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
	IsDie		= false;
	IsAir		= false;
	TickCount	= false;
	bAddScore	= false;
	IsGameClear = false;

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
	RunAnimation.clear();
	BackRunAnimation.clear();
	BackRunAnimation.clear();
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

bool Player::LostLife(RECT EnemyCollision)
{
	if (Collision.left < EnemyCollision.right &&
		Collision.top < EnemyCollision.bottom &&
		Collision.right > EnemyCollision.left &&
		Collision.bottom > EnemyCollision.top && !IsDie)
	{
		Life -= 1;
		IsDie = true;
		return true;
	}
	else
		return false;
}
bool Player::AddScore(RECT EnemyScoreCollision)
{
	if (Collision.left < EnemyScoreCollision.right &&
		Collision.top < EnemyScoreCollision.bottom &&
		Collision.right > EnemyScoreCollision.left &&
		Collision.bottom > EnemyScoreCollision.top)
	{
		bAddScore = true;
		return true;
	}
	else
		return false;
}

bool Player::GameClear(RECT EndActorCollision)
{
	if (Collision.left < EndActorCollision.right &&
		Collision.top < EndActorCollision.bottom &&
		Collision.right > EndActorCollision.left &&
		Collision.bottom > EndActorCollision.top)
	{
		pt.x = EndActorCollision.left;
		pt.y = 290;
		IsGameClear = true;
		return true;
	}
	else
		return false;
}

int Player::GetLife()
{
	return Life;
}

int Player::GetScore()
{
	return Score;
}

void Player::Update()
{
	if (IsGameClear)
	{
		IsDie = false;
	}
	else if (IsDie)
	{

	}
	else if (IsJump)
	{
		CosJump();
	}
	else if (IsRun)
	{
		IsBackRun = false;
		pt.x += Speed;
	}
	else if (IsBackRun)
	{
		IsRun = false;
		pt.x += Speed;
	}
	else
	{
		StateIdle();
	}
	Collision = { pt.x ,pt.y,pt.x + size.cx,pt.y + size.cy };
}

void Player::AnimationUpdate()
{
	if (IsGameClear)
	{
		Animation(ANI_WIN);
	}
	else if (IsDie)
	{
		Animation(ANI_DIE);
	}
	else if (IsJump)
	{
		Animation(ANI_JUMP);
	}
	else if (IsRun)
	{
		Animation(ANI_RUN);
	}
	else if (IsBackRun)
	{
		Animation(ANI_BACKRUN);
	}
	else
	{
		Animation(ANI_IDLE);
	}
}