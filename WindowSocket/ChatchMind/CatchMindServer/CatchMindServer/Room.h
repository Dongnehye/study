#pragma once
#include "Common.h"
#include "User.h"
#include "PACKET_HEADER.h"
#include <map>
#include <vector>

using namespace std;

class Room
{
public:
	int index;
	char RoomName[SHORT_BUFSIZE];
	char HostId[SHORT_BUFSIZE];
	
	bool IsStart;
	map<int, SOCKET> UserOrder;
	map<SOCKET, User*> MapUser;
	vector<DRAWLINE> VecLine;
	Room();
public:
	Room(int index);
	virtual ~Room();

	bool AddUser(SOCKET sock, User * pUser);
	bool ExitUser(SOCKET sock, User * pUser);

	void AddLine(int x0, int y0,int x1, int y1, int Color);
	void EchoLine(SOCKET sock, DRAWLINE Line);
	void ClearLine(SOCKET sock);

	void SendUserData(SOCKET sock);
	void AllSendUserData(SOCKET sock);
};