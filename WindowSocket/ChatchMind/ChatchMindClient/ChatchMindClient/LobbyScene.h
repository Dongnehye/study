#pragma once
#include "Scene.h"
#include "PACKET_HEADER.h"
#include "User.h"
#include "Button.h"
#include <map>
#include <list>

#define ID_LISTBOX 100

class LobbyScene :
	public Scene
{
	std::list<std::string> Cheat;
	std::map<int, LOBBY_DATA*> RoomInfo;
	std::map<int, int> ListBoxRoomIndex;
	std::map<int, User*> UserInfo;

	HWND CheatEdit;
	HWND hList;

	char Cheatstr[BUFSIZE];

	POINT CheatEditPos{ 70,850 };
	SIZE CHEATEditSize{ 650,20 };

	POINT RoomListEditPos{ 65,169 };
	SIZE RoomListEditSize{ 712,420 };

	POINT PlayerListPos{ 920,170 };
	POINT RoomListPos{ 200,150 };

	void RecvCheat(char * str);

	void SendCheat();
	void SendRequestLobbyData();
	void SendRequestUserData();
	void SendRoomEnter(int RoomIndex);

	LobbyScene();
public:
	LobbyScene(HWND hWnd, SOCKET _sock);
	virtual ~LobbyScene();

	virtual void ProcessPacket(char * szBuf, int len, DWORD PacketIndex);
	virtual void Update(float ElapseTime);
	virtual void Draw(HDC hdc);
	virtual void MouseLClick(LPARAM lParam);
	virtual void WindowsCommand(WPARAM wParam);
	virtual void SceneStart(HWND hWnd);
	virtual void SceneEnd(HWND hWnd);

	virtual void OperateInput(int InputKey);
};