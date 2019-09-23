#include "WinSocketMain.h"
#include <iostream>

using namespace std;

bool WinSocketMain::InitWSAdata()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return false;
	return true;
}

bool WinSocketMain::InitListen_scok()
{
	listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET)
	{
		cout << "err on socket" << endl;
		return false;
	}
	return true;
}

bool WinSocketMain::mWSAAsyncSelect(HWND hWnd)
{
	retval = WSAAsyncSelect(listen_sock, hWnd, WM_SOCKET, FD_ACCEPT | FD_CLOSE);
	if (retval == SOCKET_ERROR)
	{
		cout << "err on WSAAsyncSelect" << endl;
		return false;
	}
	return true;
}

bool WinSocketMain::mbind()
{
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(9000);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	retval = bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR)
	{
		cout << "err on bind" << endl;
		return false;
	}
	return true;
}

bool WinSocketMain::mlisten()
{
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR)
	{
		cout << "err on listen" << endl;
		return false;
	}
	return true;
}

WinSocketMain::WinSocketMain()
{
}


bool WinSocketMain::CreateSocket(HWND hWnd)
{
	if (!InitWSAdata())
		return false;
	if (!InitListen_scok())
		return false;
	if (!mWSAAsyncSelect(hWnd))
		return false;
	if (!mbind())
		return false;
	if (!mlisten())
		return false;
	return true;
}

WinSocketMain::~WinSocketMain()
{
	WSACleanup();
}
