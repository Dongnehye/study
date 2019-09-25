#pragma once
class Player
{
	Player();
public:
	char * Id;
	int Money;
	
	Player(char * _id, int _Money);
	virtual ~Player();
};