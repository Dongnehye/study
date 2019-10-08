#pragma once
#include <Windows.h>
#include <chrono>
#include "PACKET_HEADER.h"
#include "Common.h"
#include "Scene.h"
#include "LoginScene.h"
#include "LobbyScene.h"
#include "RoomScene.h"

class CatchMineMain
{
	HWND mhWnd;
	SOCKET MySock;

	char RecvBuf[BUFSIZE];
	int RecvLen;

	HWND mCheatEdit;

	HDC hMemDC[2];
	HBITMAP hBitmap[2];
	HBITMAP hOld[2];

	Scene * ArrScene[SCENE_INDEX_END];
	Scene * CurrentScene;
	void SceneChange(int SceneNumber);
	void InitScene();

	std::chrono::system_clock::time_point m_LastTime;
	float m_fElapseTime;

	void OperateInput();
	void Render();

	CatchMineMain();
public:
	CatchMineMain(HWND hWnd, SOCKET sock);
	~CatchMineMain();

	void MouseLClick(LPARAM lParam);
	void ProcessSocketMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	bool ProcessPacket(char* szBuf, int & len);

	void Updata();
};

