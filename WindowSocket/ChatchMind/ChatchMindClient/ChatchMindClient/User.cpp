#include "User.h"
#include <iostream>


User::User()
{
	IsTurn = false;
	Score = 0;;
}


User::User(int _index, const char * _id)
{
	IsTurn = false;
	Score = NULL;;
	index = _index;
	strcpy(id, _id);
	Cheat[0] = '\0';
	CooldownCheat = NULL;
}

User::~User()
{
}

void User::SetPosition(int _x, int _y)
{
	x = _x;
	y = _y;
}

POINT User::GetPosition()
{
	POINT pt;
	pt.x = x;
	pt.y = y;

	return pt;
}

void User::Reset()
{
	IsTurn = false;
	Score = 0;;
}

char * User::Getid()
{
	return id;
}

void User::SetCheat(char * _cheat)
{
	strcpy(Cheat, _cheat);
}

char * User::GetCheat()
{
	return Cheat;
}

void User::SetCooldownCheat(int count)
{
	CooldownCheat = count;
}

bool User::IsCheatCooldownOver()
{
	if (CooldownCheat <= 0)
	{
		return true;
	}
	return false;
}

void User::DecreaseCooldownCheat()
{
	--CooldownCheat;
}
