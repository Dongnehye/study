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

	HWND mCheatEdit;

	HDC hMemDC[2];
	HBITMAP hBitmap[2];
	HBITMAP hOld[2];

	SOCKET sock;
	map<int, Player*> g_mapPlayer;
	int g_iIndex = 0;
	
	chrono::system_clock::time_point m_LastTime;
	float m_fElapseTime;

	Scene * ArrScene[3];
	Scene * CurrentScene;
	LobbyScene * Lobby;
	LoginScene * Login;
	GameTableScene * GameTable;

	void SceneInit();
	void SceneChange(int SceneNumber);
	bool IsLogin;
	bool IsLobby;
	bool isGameTable;

	void OperateInput();
	void Render();

	BadugiMain();
public:
	BadugiMain(HWND hWnd,SOCKET _sock);

	void MouseLClick(LPARAM lParam);

	void ProcessPacket(char* szBuf, int len);

	void Updata();
	virtual ~BadugiMain();
};