#pragma once
#include <WinSock2.h>
#include <Windows.h>

#define WM_SOCKET (WM_USER+1)
#define SERVERPORT 9000

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
	bool CreateWSAAsyncSocket(HWND hWnd);
	bool CreateSocket();
	SOCKET GetListenSock();

	virtual ~WinSocketMain();
};