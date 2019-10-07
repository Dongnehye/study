#pragma once
#include <Windows.h>
#include <chrono>
#include "PACKET_HEADER.h"
#include "Common.h"



class CatchMineMain
{
	HWND mhWnd;
	SOCKET MyScok;

	char RecvBuf[BUFSIZE];
	int RecvLen;

	HWND mCheatEdit;

	HDC hMemDC[2];
	HBITMAP hBitmap[2];
	HBITMAP hOld[2];

	std::chrono::system_clock::time_point m_LastTime;
	float m_fElapseTime;

	void OperateInput();

	CatchMineMain();
public:
	CatchMineMain(HWND hWnd, SOCKET sock);
	~CatchMineMain();

	void MouseLClick(LPARAM lParam);
	void ProcessSocketMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	bool ProcessPacket(char* szBuf, int & len);

	void Updata();
};

