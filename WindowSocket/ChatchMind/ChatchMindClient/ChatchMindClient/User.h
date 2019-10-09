#pragma once
#include "Common.h"

class User
{
	int index;
	char id[SHORT_BUFSIZE];
	bool IsTurn;
	int Score;

	User();
public:
	User(int index, const char * id);
	virtual ~User();

	void Reset();
	char * Getid();
};