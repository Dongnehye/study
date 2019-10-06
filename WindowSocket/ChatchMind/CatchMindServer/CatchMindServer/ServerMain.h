#pragma once
#include "Common.h"
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
	bool AddUser(SOCKET sock);
	User * GetUser(SOCKET sock);

	ServerMain();
	virtual ~ServerMain();
	void AcceptSocket(SOCKET ClientSock, HANDLE hcp);
};

