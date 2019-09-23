#include "Player.h"



Player::Player()
{
	Id = nullptr;
	Money = 0;
	RoomIndex = 0;
}

Player::Player(char * _id, int _Money)
{
	Id = _id;
	Money = _Money;
	RoomIndex = 0;
}


Player::~Player()
{
}
