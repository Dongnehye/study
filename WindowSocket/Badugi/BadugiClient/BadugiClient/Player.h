#pragma once
#include "CommonHeader.h"
#include <list>

class Player
{
	Player();
public:
	int x;
	int y;

	char Id[IDPWSIZE];
	int Money;
	
	std::list<int> card;

	void SetPosition(int x, int y);
	Player(char * _id, int _Money);
	virtual ~Player();
};