#pragma once
#include "CommonHeader.h"
#include <list>
#include <Windows.h>

class Player
{
	Player();
public:
	int x;
	int y;

	char Id[IDPWSIZE];
	int Money;
	int Batting;
	bool IsDie = false;
	bool IsTurn = false;
	std::list<int> card;

	void SetPosition(int x, int y);
	Player(char * _id, int _Money);
	virtual ~Player();


};