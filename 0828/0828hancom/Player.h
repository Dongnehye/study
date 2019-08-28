#pragma once
#include <Windows.h>
#include "GameManager.h"

class Player
{
	int Hp;
	char str[256];
	GameManager * gm;

	RECT TownRect;
	RECT BeachRect;

public:
	Player();
	~Player();
	void Init(GameManager * _gm);
	void Input(WPARAM wParam);
	void InputEnter(WPARAM wParam);
	void Draw(HWND hWnd);
};