#include "Player.h"



Player::Player()
{

}

Player::Player(HDC hdc)
{
	Actor::Actor(hdc);

	Idle.Init(hdc,"Circus\\player0.bmp");
	Jump.Init(hdc, "Circus\\player2.bmp");
	Run1.Init(hdc,"Circus\\player1.bmp");
	Run2.Init(hdc,"Circus\\player2.bmp");
	Win1.Init(hdc,"Circus\\win.bmp");
	Win2.Init(hdc,"Circus\\win2.bmp");
	Die.Init(hdc,"Circus\\die.bmp");
}


Player::~Player()
{
}

void Player::ActiveMove(int x)
{
	pt.x += x;
}

void Player::ActiveJump()
{
}