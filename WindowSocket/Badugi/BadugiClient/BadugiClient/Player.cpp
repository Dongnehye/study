#include "Player.h"
#include <iostream>


Player::Player()
{
	strcpy(Id, "\0");
	Money = 0;

}

void Player::SetPosition(int _x, int _y)
{
	x = _x;
	y = _y;
}

Player::Player(char * _id, int _Money)
{
	strcpy(Id, _id);
	Money = _Money;
	IsDie = false;
}


Player::~Player()
{
}
