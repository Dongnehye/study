#pragma once
#include "Scene.h"
#include "PACKET_HEADER.h"
#include <map>
#include <list>

#define CHEAT_EDIT 3

class LobbyScene :
	public Scene
{
	std::list<std::string> Cheat;

	HWND CheatEdit;
	char Cheatstr[BUFSIZE];

	POINT CheatEditPos{ 30,850 };

	SIZE CHEATEditSize{ 350,30 };

	void RectRoomInit(HDC hdc);

	void RecvCheat(char * str);

	void SendCheat();

	LobbyScene();
public:
	LobbyScene(HWND hWnd, SOCKET _sock);
	virtual ~LobbyScene();

	virtual void ProcessPacket(char * szBuf, int len, DWORD PacketIndex);
	virtual void Update(float ElapseTime);
	virtual void Draw(HDC hdc);
	virtual void MouseLClick(LPARAM lParam);
	virtual void SceneStart(HWND hWnd);
	virtual void SceneEnd(HWND hWnd);

	virtual void OperateInput(int InputKey);
};

