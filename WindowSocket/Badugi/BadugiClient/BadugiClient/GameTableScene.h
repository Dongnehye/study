#pragma once
#include "Scene.h"
class GameTableScene :
	public Scene
{
	GameTableScene();
public:
	GameTableScene(HWND hWnd);
	virtual ~GameTableScene();

	virtual void Draw(HDC hdc);
};

