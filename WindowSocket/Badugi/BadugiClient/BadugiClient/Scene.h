#pragma once
#include "PACKET_HEADER.h"
#include "Bitmap.h"
#include "Button.h"

class Scene
{
protected:
	int Index;
	Bitmap * Background;
	SOCKET sock;
	POINT CursorPos;
public:
	Scene();
	virtual ~Scene();

	virtual void Update() = 0;
	virtual void Draw(HDC hdc) = 0;
	virtual void MouseLClick(LPARAM lParam) = 0;
	virtual void SceneStart(HWND hWnd) = 0;
	virtual void SceneEnd(HWND hWnd) = 0;
	Scene* SceneChange(Scene * PreviousScene, HWND hWnd);
};