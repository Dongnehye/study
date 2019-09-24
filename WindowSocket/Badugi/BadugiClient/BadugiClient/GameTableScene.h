#pragma once
#include "Scene.h"
class GameTableScene :
	public Scene
{
	GameTableScene();
public:
	GameTableScene(HWND hWnd, SOCKET _sock);
	virtual ~GameTableScene();

	virtual void Update();
	virtual void Draw(HDC hdc);
	virtual void MouseLClick(LPARAM lParam);
	virtual void SceneStart(HWND hWnd);
	virtual void SceneEnd(HWND hWnd);

};

