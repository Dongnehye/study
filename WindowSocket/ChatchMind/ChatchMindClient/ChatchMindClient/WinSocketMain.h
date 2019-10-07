#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include "Common.h"

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
	bool SocketConnect();
	bool Socketlisten();
	
public:
	WinSocketMain();
	bool CreateWSAAsyncSocket(HWND hWnd);
	bool CreateSocket();

	bool CreateWSAAsyncClientSocket(HWND hWnd);
	bool ConnectServer(HWND hWnd);
	SOCKET GetListenSock();

	virtual ~WinSocketMain();
};