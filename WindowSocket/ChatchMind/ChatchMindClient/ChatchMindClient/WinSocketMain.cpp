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

bool WinSocketMain::InitWSAAsyncSelect(HWND hWnd)
{
	retval = WSAAsyncSelect(listen_sock, hWnd, WM_SOCKET, FD_ACCEPT | FD_CLOSE);
	if (retval == SOCKET_ERROR)
	{
		cout << "err on WSAAsyncSelect" << endl;
		return false;
	}
	return true;
}

bool WinSocketMain::Socketbind()
{
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(SERVERPORT);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	retval = bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR)
	{
		cout << "err on bind" << endl;
		return false;
	}
	return true;
}

bool WinSocketMain::SocketConnect()
{
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(9000);
	//serveraddr.sin_addr.s_addr = inet_addr("10.30.10.209");
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	int retval = connect(listen_sock, (sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR)
	{
		//cout << "err on connect" << endl;
		return false;
	}
	return true;
}

bool WinSocketMain::Socketlisten()
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


bool WinSocketMain::CreateWSAAsyncSocket(HWND hWnd)
{
	if (!InitWSAdata())
		return false;
	if (!InitListen_scok())
		return false;
	if (!InitWSAAsyncSelect(hWnd))
		return false;
	if (!Socketbind())
		return false;
	if (!Socketlisten())
		return false;
	return true;
}

bool WinSocketMain::CreateSocket()
{
	if (!InitWSAdata())
		return false;
	if (!InitListen_scok())
		return false;
	if (!Socketbind())
		return false;
	if (!Socketlisten())
		return false;
	return true;
}

bool WinSocketMain::CreateClientSocket(HWND hWnd)
{
	if (!InitWSAdata())
		return false;
	if (!InitListen_scok())
		return false;
	return true;
}

bool WinSocketMain::WSAAsyncClientSocket(HWND hWnd)
{
	retval = WSAAsyncSelect(listen_sock, hWnd, WM_SOCKET, FD_READ | FD_CLOSE);
	if (retval == SOCKET_ERROR)
	{
		return false;
	}
	return true;
}

bool WinSocketMain::CreateWSAAsyncClientSocket(HWND hWnd)
{
	if (!CreateClientSocket(hWnd))
		return false;
	if (!SocketConnect())
		return false;
	if (!WSAAsyncClientSocket(hWnd))
		return false;
	return true;
}

SOCKET WinSocketMain::GetListenSock()
{
	return listen_sock;
}

WinSocketMain::~WinSocketMain()
{
	closesocket(listen_sock);
	WSACleanup();
}
