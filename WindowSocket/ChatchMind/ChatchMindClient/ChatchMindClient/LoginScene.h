#pragma once
#include "Scene.h"
#include "PACKET_HEADER.h"

#define ID_EDIT 1
#define PW_EDIT 2

class LoginScene :
	public Scene
{
	char Idstr[SHORT_BUFSIZE];
	char Pwstr[SHORT_BUFSIZE];

	HWND IdEdit;
	HWND PwEdit;

	POINT IdEditPos{ 465 , 520 };
	POINT PwEditPos{ 465 ,597 };
	SIZE IdEditSize{ 301,60 };
	SIZE PWEditSize{ 301,60 };

	Button * LoginButton;

	LoginScene();
public:
	void SendLogin();
	LoginScene(HWND hWnd, SOCKET sock);

	virtual ~LoginScene();

	virtual void ProcessPacket(char * szBuf, int len, DWORD PacketIndex);
	virtual void Update(float ElapseTime);
	virtual void Draw(HDC hdc);
	virtual void MouseLClick(LPARAM lParam);
	virtual void WindowsCommand(WPARAM wParam);
	virtual void SceneStart(HWND hWnd);
	virtual void SceneEnd(HWND hWnd);

	virtual void OperateInput(int InputKey);
};

