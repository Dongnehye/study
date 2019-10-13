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

	POINT IdEditPos{ 548 ,679 };
	POINT PwEditPos{ 548 ,711 };
	SIZE IdEditSize{ 169,29 };
	SIZE PWEditSize{ 169,29 };

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

