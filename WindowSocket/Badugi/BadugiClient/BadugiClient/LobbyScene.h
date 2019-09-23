#pragma once
#include "Scene.h"

class LobbyScene 
	: public Scene
{
	LobbyScene();
public:
	LobbyScene(HWND hWnd);
	virtual ~LobbyScene();

	virtual void Draw(HDC hdc);
};

