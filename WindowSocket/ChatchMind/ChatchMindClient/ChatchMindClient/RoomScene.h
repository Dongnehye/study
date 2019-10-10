#pragma once
#include "Scene.h"
#include "User.h"
#include "Common.h"
#include "PACKET_HEADER.h"
#include <map>
#include <vector>

#define CHEAT_EDIT 4

class RoomScene :
	public Scene
{
	int MyIndex;
	std::map<int, User*> MapUser;


	HPEN hPen, hOldPen;
	int x0, y0;
	int x1, y1;
	bool Drawing;
	std::vector<DRAWLINE> VecLine;


	HWND CheatEdit;
	char Cheatstr[BUFSIZE];
	POINT CheatEditPos{ 622,710 };
	SIZE CHEATEditSize{ 277,28 };

	Button * ExitButton;

	void SendRequestUserData();
	void SendCheat();

	void ExitGame();

	RoomScene();
public:
	RoomScene(HWND hWnd,SOCKET _sock);
	virtual ~RoomScene();

	virtual void ProcessPacket(char * szBuf, int len, DWORD PacketIndex);
	virtual void Update(float ElapseTime);
	virtual void Draw(HDC hdc);
	virtual void MouseLClick(LPARAM lParam);
	virtual void MouseMove(LPARAM lParam);
	virtual void MouseLClickUp(LPARAM lParam);
	virtual void WindowsCommand(WPARAM wParam);
	virtual void SceneStart(HWND hWnd);
	virtual void SceneEnd(HWND hWnd);

	virtual void OperateInput(int InputKey);
};