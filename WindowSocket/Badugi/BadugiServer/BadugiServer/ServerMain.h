#pragma once
#include <Windows.h>
#include <functional>
#include <map>
#include <vector>
#include "PACKET_HEADER.H"
#include "CommonHeader.h"
#include "User.h"
#include "Room.h"
#include "Lobby.h"
#include "GameTable.h"

#define WM_SOCKET (WM_USER+1)

class ServerMain
{
	int g_iIndex = 0;
	std::map<SOCKET, User*> mapUser;
	std::map<int, GameTable*> mapRoom;
	Lobby * mLobby;

	void RoomInit();
	bool CheckLogin(const char * Id, const char * pw, int &Money);
	void SendCardRefresh(SOCKET sock,User * pUser);
	void SendAllCardRefresh(SOCKET sock, User * pUser);

public:
	ServerMain();
	virtual ~ServerMain();

	void ProcessSocketMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	bool ProcessPacket(SOCKET sock, User* pUser, char* szBuf, int& len);
	void SwitchPacket(SOCKET sock, User* pUser, char* szBuf, int& len, WORD Index);

	void err_display(int errcode);
	void err_display(const char* szMsg);
};