#pragma once
#include "Common.h"
#include "User.h"
#include "PACKET_HEADER.h"
#include <map>

using namespace std;

class Room
{
public:
	int index;
	char RoomName[SHORT_BUFSIZE];
	char HostId[SHORT_BUFSIZE];
	
	bool IsStart;
	map<SOCKET, User*> MapUser;
	Room();
public:
	Room(int index);
	virtual ~Room();

	bool AddUser(SOCKET sock, User * pUser);
	bool ExitUser(SOCKET sock, User * pUser);

	void SendUserData(SOCKET sock);
	void AllSendUserData(SOCKET sock);
};