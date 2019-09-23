#pragma once

#include <WinSock2.h>
#include <windows.h>
#include <map>
#include <chrono>
#include "Player.h"
#include "PACKET_HEADER.h"
#include "Scene.h"
#include "LoginScene.h"
#include "LobbyScene.h"
#include "GameTableScene.h"

#define BUFSIZE 512
#define FPS 60

using namespace std;

class BadugiMain
{
	HWND mhWnd;
	HDC hMemDC[2];
	HBITMAP hBitmap[2];
	HBITMAP hOld[2];

	SOCKET sock;
	map<int, Player*> g_mapPlayer;
	map<int, LOBBY_DATA*> RoomInfo;
	int g_iIndex = 0;
	
	chrono::system_clock::time_point m_LastTime;
	float m_fElapseTime;

	Scene * ArrScene[3];
	Scene * CurrentScene;
	LobbyScene * Lobby;
	LoginScene * Login;
	GameTableScene * GameTable;

	const char * g_Id = "123";
	const char * g_Pw = "456";

	void SceneChange();
	bool IsLogin;
	bool IsLobby;
	bool isGameTable;

	BadugiMain();
public:
	BadugiMain(HWND hWnd,SOCKET _sock);
	void SendLogin(const char * Id, const char * Pw);
	void SetId(char * Id);
	void SetPw(char * Pw);
	void SendRoomEnter(int RoomIndex);
	void SendLobbyRefresh();

	void SceneInit();
	void ProcessPacket(char* szBuf, int len);

	void Updata();
	void OperateInput();
	void Render();
	virtual ~BadugiMain();
};