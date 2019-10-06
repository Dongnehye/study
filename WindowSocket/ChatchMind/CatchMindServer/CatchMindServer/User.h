#pragma once
#include "Common.h"

class User
{

public:
	int Index;
	WSAOVERLAPPED overlapped;
	char buf[BUFSIZE + 1];
	int recvbytes;
	WSABUF wsabuf;

	User();
	virtual ~User();

	void 
};