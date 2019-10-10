#pragma once
#include <WinSock2.h>

#define BUFSIZE 512
#define SHORT_BUFSIZE 20

#define LOBBYINDEX 0

struct SOCKETINFO
{
	WSAOVERLAPPED overlapped;
	char buf[BUFSIZE + 1];
	WSABUF wsabuf;
	int recvbytes;
	int sendbytes;
};
