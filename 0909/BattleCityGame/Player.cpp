#include "Player.h"



Player::Player()
{
}


Player::Player(HDC hdc)
{
	Position.x = 0;
	Position.y = 0;
	x = 0;
	y = 0;
	Model = new Bitmap(hdc, "BattleCity\\tank_up_00.bmp");
}

void Player::SetPosition(POINT pt)
{
	Position = pt;
}

void Player::SetPositionX(float _x)
{
	x += _x;
}

void Player::SetPositionY(float _y)
{
	y += _y;
}

float Player::GetPositionX()
{
	return x;
}

float Player::GetPositionY()
{
	return y;
}

Player::~Player()
{
}

void Player::Update()
{
}