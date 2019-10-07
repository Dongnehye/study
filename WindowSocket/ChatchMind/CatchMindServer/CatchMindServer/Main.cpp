#pragma comment(lib,"ws2_32")
#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include <iostream>
#include <process.h>
#include "WinSocketMain.h"
#include "ServerMain.h"
#include "User.h"
#include "Common.h"

DWORD WINAPI WorkerThread(LPVOID arg);

ServerMain * Server;


void err_display(int errcode)
{
	LPVOID lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[오류]%s", lpMsgBuf);
	LocalFree(lpMsgBuf);
}

void err_display(const char * szMsg)
{
	LPVOID lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s]%s\n", szMsg, lpMsgBuf);
	LocalFree(lpMsgBuf);
}

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
	//for (int i = 0; i < 2; i++)
	{
		hThread = (HANDLE)_beginthreadex(NULL, 0, (_beginthreadex_proc_type)WorkerThread, hcp, 0, NULL);
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
		SOCKETINFO * ptr;
		retval = GetQueuedCompletionStatus(hcp, &cbTranferred,
			(LPDWORD)&client_sock, (LPOVERLAPPED*)&ptr, INFINITE);
		SOCKADDR_IN clientaddr;
		int addrlen = sizeof(clientaddr);
		getpeername(client_sock, (SOCKADDR*)&clientaddr, &addrlen);

		if (retval == 0 || cbTranferred == 0)
		{
			if (retval == 0)
			{
				DWORD temp1, temp2;
				WSAGetOverlappedResult(client_sock, &ptr->overlapped,
					&temp1, FALSE, &temp2);
				err_display("WSAGetOverlappedResult()");
			}
			closesocket(client_sock);
			printf("[TCP 서버] 클라이언트 종료 : IP 주소 = %s, 포트 번호 = %d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
			delete ptr;
			
			continue;
		}
		User * pUser = Server->GetUser(client_sock);

		while (true)
		{
			//cout << this_thread::get_id() << endl;
			if (Server->ProcessPacket(client_sock,pUser,ptr->buf, cbTranferred))
			{
				break;
			}
			else
			{
				if (pUser->len < sizeof(PACKET_HEADER))
					break;
			}
		}
	}
	return 0;
}