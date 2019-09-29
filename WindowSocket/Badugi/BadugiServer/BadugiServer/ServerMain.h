#pragma once
#include <Windows.h>
#include <map>
#include <vector>
#include "LobbyServer.h"
#include "PACKET_HEADER.H"
#include "CommonHeader.h"
#include "User.h"
#include "Room.h"
#include "GameTable.h"

#define WM_SOCKET (WM_USER+1)

class ServerMain
{
	int g_iIndex = 0;
	std::map<SOCKET, User*> mapUser;
	LobbyServer * Lobby;

	void AddUser(SOCKET sock);
	bool CheckLogin(const char * Id, const char * pw, int &Money);
	void SendLogin(SOCKET sock, char * Buf,int len);

public:
	ServerMain();
	virtual ~ServerMain();

	void ProcessSocketMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	bool ProcessPacket(SOCKET sock, User* pUser, char* szBuf, int& len);

	void err_display(int errcode);
	void err_display(const char* szMsg);
};