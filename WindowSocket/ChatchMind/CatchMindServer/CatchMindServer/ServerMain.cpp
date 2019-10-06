#include "ServerMain.h"

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