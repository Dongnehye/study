#pragma once
#include "Scene.h"
#include "CommonHeader.h"
#include <windows.h>
#include <map>
#include <list>

#define CHEAT_EDIT 3

class LobbyScene 
	: public Scene
{
	LobbyScene();
	
	std::map<int, LOBBY_DATA*> RoomInfo;
	std::map<int, const char*> RoomUserSize;
	std::list<std::string> Cheat;

	HWND CheatEdit;
	char Cheatstr[BUFSIZE];

	POINT CheatEditPos{ 30,850 };

	SIZE CHEATEditSize{ 350,30 };

	Button * RoomButton[ROOMSIZE];
	RECT RoomEnterButton[ROOMSIZE];

	Button * CheatEnter;
	void RectRoomInit(HDC hdc);

	void SendRoomEnter(int RoomIndex);
	void SendLobbyRefresh();
	void SendCheat();

public:
	LobbyScene(HWND hWnd, SOCKET _sock);
	virtual ~LobbyScene();

	void RecvCheat(char * str);
	void RoomInfoRefresh(PACKET_SEND_LOBBYDATA packet);
	virtual void Update(float ElapseTime);
	virtual void Draw(HDC hdc);
	virtual void MouseLClick(LPARAM lParam);
	virtual void SceneStart(HWND hWnd);
	virtual void SceneEnd(HWND hWnd);

};

