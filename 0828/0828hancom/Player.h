#pragma once
#include <Windows.h>
#include "GameManager.h"

class Player
{
	int Hp;
	char str[256];
	char name[256];
	GameManager * gm;

	RECT TownRect;
	RECT BeachRect;
	RECT InputRect;
	void GameOver();

public:
	Player();
	~Player();
	void Init(GameManager * _gm);
	void Input(WPARAM wParam);
	void InputEnter(WPARAM wParam,bool &_GameStart);
	void Draw(HWND hWnd);
	void Update();
};