#pragma once
#include "Common.h"
#include <Windows.h>

class User
{
	int index;
	char id[SHORT_BUFSIZE];
	bool IsTurn;
	int Score;

	int x;
	int y;

	char Cheat[BUFSIZE];
	int CooldownCheat;

	User();
public:
	User(int index, const char * id);
	virtual ~User();

	void SetPosition(int x, int y);
	POINT GetPosition();

	void Reset();
	char * Getid();

	void IncreaseScore();
	void ResetScore();
	void SetCheat(char * cheat);
	char * GetCheat();
	int GetScore();
	void SetCooldownCheat(int count);
	bool IsCheatCooldownOver();
	void DecreaseCooldownCheat();
};