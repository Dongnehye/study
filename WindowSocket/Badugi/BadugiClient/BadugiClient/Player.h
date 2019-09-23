#pragma once
class Player
{
	Player();
public:
	char * Id;
	int Money;
	int RoomIndex;
	
	Player(char * _id, int _Money);
	virtual ~Player();
};