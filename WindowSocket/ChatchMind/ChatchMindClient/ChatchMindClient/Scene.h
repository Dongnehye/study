#pragma once
#include "Common.h"
#include "Button.h"

class Scene
{
protected:
	int MyIndex;
	Bitmap * Background;
	SOCKET sock;
	POINT CursorPos;

public:
	Scene();
	virtual ~Scene();

	virtual void SetMyIndex(int MyIndex);
	virtual void ProcessPacket(char * szBuf, int len, DWORD PacketIndex) = 0;
	virtual void Update(float ElapseTime) = 0;
	virtual void Draw(HDC hdc) = 0;
	virtual void MouseLClick(LPARAM lParam) = 0;
	virtual void WindowsCommand(WPARAM wParam) = 0;
	virtual void SceneStart(HWND hWnd) = 0;
	virtual void SceneEnd(HWND hWnd) = 0;
	virtual void OperateInput(int InputKey) = 0;

	virtual void MouseMove(LPARAM lParam);
	virtual void MouseLClickUp(LPARAM lParam);
	virtual void MouseRClick(LPARAM lParam);
	virtual void MouseRClickUp(LPARAM lParam);

	Scene * SceneChange(Scene * PreviousScene, HWND hWnd);
};

