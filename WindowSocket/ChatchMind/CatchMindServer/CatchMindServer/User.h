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

	User();
	virtual ~User();

};