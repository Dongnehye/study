#pragma comment(lib,"ws2_32")
#include <stdlib.h>
#include <stdio.h>
#include "WinSocketMain.h"
#include "ServerMain.h"
#include "User.h"
#include "Common.h"

DWORD WINAPI WorkerThread(LPVOID arg);

ServerMain * Server;

int main(int argc, char * args[])
{
	int retval;
	WinSocketMain * WinSocket = new WinSocketMain();

	WinSocket->CreateSocket();

	HANDLE hcp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if (hcp == NULL)
		return 1;

	SYSTEM_INFO si;
	GetSystemInfo(&si);

	HANDLE hThread;
	for (int i = 0; i < (int)si.dwNumberOfProcessors * 2; i++)
	{
		hThread = CreateThread(NULL, 0, WorkerThread, hcp, 0, NULL);
		if (hThread == NULL)
			return 1;
		CloseHandle(hThread);
	}

	Server = new ServerMain();

	Server->AcceptSocket(WinSocket->GetListenSock(), hcp);

	WSACleanup();
	delete Server;
	return 0;

}
DWORD WINAPI WorkerThread(LPVOID arg)
{
	int retval;
	HANDLE hcp = (HANDLE)arg;

	while (1)
	{
		DWORD cbTranferred;
		SOCKET client_sock;
		SOCKETINFO *ptr;
		retval = GetQueuedCompletionStatus(hcp, &cbTranferred,
			(LPDWORD)&client_sock, (LPOVERLAPPED*)&ptr, INFINITE);
		SOCKADDR_IN clientaddr;
		int addrlen = sizeof(clientaddr);
		getpeername(ptr->sock, (SOCKADDR*)&clientaddr, &addrlen);

		if (retval == 0 || cbTranferred == 0)
		{
			if (retval == 0)
			{
				DWORD temp1, temp2;
				WSAGetOverlappedResult(ptr->sock, &ptr->overlapped,
					&temp1, FALSE, &temp2);
				err_display("WSAGetOverlappedResult()");
			}
			closesocket(ptr->sock);
			printf("[TCP 서버] 클라이언트 종료 : IP 주소 = %s, 포트 번호 = %d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
			delete ptr;
			continue;
		}
		if (ptr->recvbytes == 0)
		{
			ptr->recvbytes = cbTranferred;
			ptr->buf[ptr->recvbytes] = '\0';
			printf("[TCP%s:%d]%s\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port), ptr->buf);
			//packet 처리.
		}

		if (ptr->recvbytes > 0)
		{

		}
		else
		{
			ptr->recvbytes = 0;
			ZeroMemory(&ptr->overlapped, sizeof(ptr->overlapped));
			ptr->wsabuf.buf = ptr->buf;
			ptr->wsabuf.len = BUFSIZE;

			DWORD recvbytes;
			DWORD flags = 0;
			retval = WSARecv(ptr->sock, &ptr->wsabuf, 1, &recvbytes, &flags, &ptr->overlapped, NULL);
			if (retval == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSA_IO_PENDING)
				{
					err_display("WSARecv()");
				}
				continue;
			}
		}
	}
	return 0;
}