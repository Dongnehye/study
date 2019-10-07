#include "ServerMain.h"
#include <iostream>

using namespace std;

void ServerMain::err_display(int errcode)
{
	LPVOID lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[오류]%s", lpMsgBuf);
	LocalFree(lpMsgBuf);
}

void ServerMain::err_display(const char * szMsg)
{
	LPVOID lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s]%s\n", szMsg, lpMsgBuf);
	LocalFree(lpMsgBuf);
}

bool ServerMain::AddUser(SOCKET sock)
{
	User * user = new User();
	if (user == NULL)
		return false;

	ZeroMemory(&user->overlapped, sizeof(user->overlapped));
	user->recvbytes = 0;
	user->wsabuf.buf = user->buf;
	user->wsabuf.len = BUFSIZE;
	user->Index = gIndex++;
	MapUser.insert(make_pair(sock, user));

	return true;
}

User * ServerMain::GetUser(SOCKET sock)
{
	return MapUser[sock];
}

ServerMain::ServerMain()
{
	gIndex = 0;
}


ServerMain::~ServerMain()
{
}

void ServerMain::AcceptSocket(SOCKET ClientSock, HANDLE hcp)
{
	int retval;
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	DWORD recvbytes, flags;

	while (1)
	{
		addrlen = sizeof(clientaddr);
		client_sock = accept(ClientSock, (SOCKADDR *)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET)
		{
			err_display("accpet()");
			break;
		}
		printf("[TCP 서버] 클라이언트 접속 : IP 주소 = %s , 포트번호 = %d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		CreateIoCompletionPort((HANDLE)client_sock, hcp, client_sock, 0);

		if (!AddUser(client_sock))
			break;

		flags = 0;
		retval = WSARecv(client_sock, &MapUser[client_sock]->wsabuf, 1, &recvbytes,
			&flags, &MapUser[client_sock]->overlapped, NULL);
		if (retval == SOCKET_ERROR)
		{
			if (WSAGetLastError() != ERROR_IO_PENDING)
			{
				err_display("WSARecv()");
			}
			continue;
		}
	}
}

bool ServerMain::ProcessPacket(SOCKET sock, User * pUser, char * Buf, DWORD & len)
{
	if (len > 0)
	{
		pUser->len += len;
		len = 0;
	}
	if (pUser->len < sizeof(PACKET_HEADER))
		return false;

	PACKET_HEADER header;
	memcpy(&header, pUser->buf, sizeof(header));

	if (pUser->len < header.wLen)
		return false;

	switch (header.wIndex)
	{
	case PACKET_INDEX_SEND_LOGIN:
	{
		PACKET_LOGIN packet;
		memcpy(&packet, Buf, header.wLen);
		cout << packet.id << endl;

		send(sock, (const char *)&packet,packet.header.wLen,0);
	}
	break;
	}
	memcpy(&pUser->buf, &pUser->buf[header.wLen], pUser->len - header.wLen);
	pUser->len -= header.wLen;

	return true;

}

void ServerMain::EraseSocket(SOCKET sock)
{
	delete MapUser[sock];
	MapUser.erase(sock);
}
