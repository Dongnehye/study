#pragma once
#include "Scene.h"
#include "PACKET_HEADER.h"
#include "User.h"
#include <map>
#include <list>

#define CHEAT_EDIT 3

class LobbyScene :
	public Scene
{
	std::list<std::string> Cheat;
	//std::map<int, LOBBY_DATA_INFO*> RoomInfo;
	std::map<int, User*> UserInfo;

	HWND CheatEdit;
	char Cheatstr[BUFSIZE];

	POINT CheatEditPos{ 70,850 };

	SIZE CHEATEditSize{ 650,20 };

	void RectRoomInit(HDC hdc);

	void RecvCheat(char * str);

	void SendCheat();
	void SendRequestLobbyData();
	void SendRequestUserData();

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

