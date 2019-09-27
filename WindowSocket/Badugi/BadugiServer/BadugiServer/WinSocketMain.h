#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <Windows.h>
#include "CommonHeader.h"

#define WM_SOCKET (WM_USER+1)

class WinSocketMain
{
	WSADATA wsa;
	SOCKET listen_sock;

	int retval;

	bool InitWSAdata();
	bool InitListen_scok();
	bool InitWSAAsyncSelect(HWND hWnd);

	bool Socketbind();
	bool Socketlisten();
	
public:
	WinSocketMain();
	bool CreateSocket(HWND hWnd);
	virtual ~WinSocketMain();
};