#pragma once
#include "Common.h"
#include "User.h"
#include <map>

using namespace std;

class Room
{
	int index;
	char RoomName[SHORT_BUFSIZE];
	
	map<SOCKET, User*> MapUser;
	Room();
public:
	Room(int index);
	virtual ~Room();

	void AddUser(SOCKET sock, User * pUser);
};