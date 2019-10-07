#pragma once
#include "Common.h"
#include "PACKET_HEADER.h"
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include "User.h"

using namespace std;

class ServerMain
{
	int gIndex;
	SOCKET listen_sock;
	map<SOCKET, User*> MapUser;

public:
	void err_display(int errcode);
	void err_display(const char * szMsg);
	bool AddUser(SOCKET sock);
	User * GetUser(SOCKET sock);

	ServerMain();
	virtual ~ServerMain();

	void AcceptSocket(SOCKET ClientSock, HANDLE hcp);
	bool ProcessPacket(SOCKET sock, User * pUser, char * Buf, DWORD & len);

	void EraseSocket();
};

