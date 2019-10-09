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
	Score = 0;;
	index = _index;
	strcpy(id, _id);
}

User::~User()
{
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
