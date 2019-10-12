#pragma once
#include "Common.h"
#include "User.h"
#include "PACKET_HEADER.h"
#include "LobbyServer.h"
#include <stdlib.h>
#include <stdio.h>
#include <map>

using namespace std;

class ServerMain
{
	int gIndex;
	SOCKET listen_sock;
	map<SOCKET, User*> MapUser;

	LobbyServer * Lobby;

	bool CheckLogin(const char * Id, const char * pw);
	void SendLogin(SOCKET sock, bool _IsLogin);



public:
	void err_display(int errcode);
	void err_display(const char * szMsg);
	bool AddUser(SOCKET sock);
	User * GetUser(SOCKET sock);

	ServerMain();
	virtual ~ServerMain();

	void AcceptSocket(SOCKET ClientSock, HANDLE hcp);
	bool ProcessPacket(SOCKET sock, User * pUser, char * Buf, DWORD & len);

	void EraseSocket(SOCKET sock);

	void IncreaseTime();
};