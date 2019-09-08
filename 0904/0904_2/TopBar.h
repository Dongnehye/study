#pragma once
#include "CommonHeader.h"
#include "Player.h"
#include "StringTile.h"
#include "Bitmap.h"
#include <Windows.h>

class TopBar
{
	Bitmap Model;
	StringTile * Score;
	StringTile * Bonus;
	StringTile * HiScore;
	Bitmap life[MAXLIFE];

	int PlayerLife;

public:
	TopBar();
	TopBar(HDC hdc);
	virtual ~TopBar();

	void DrawTopBar(HDC hdc, int PlayerStartRunDistance);
	void Update(Player * player,int Bonus,int HiScore);
};