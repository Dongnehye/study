#pragma once
#include "Common.h"

class User
{

public:
	WSAOVERLAPPED overlapped;
	char buf[BUFSIZE + 1];
	WSABUF wsabuf;
	int recvbytes;
	int Index;
	int len;

	int MyIndexRoom;
	int RoomIndex;
	int CharacterIndex;
	char id[SHORT_BUFSIZE];

	int Score;

	User();
	virtual ~User();
};