#pragma once
#include <WinSock2.h>
#include <stdio.h>

#define BUFSIZE 512

struct SOCKETINFO
{
	WSAOVERLAPPED overlapped;
	char buf[BUFSIZE + 1];
	WSABUF wsabuf;
	int recvbytes;
	int sendbytes;
};
