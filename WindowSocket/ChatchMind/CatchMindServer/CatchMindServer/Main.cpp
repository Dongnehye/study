#pragma comment(lib,"ws2_32")
#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include <iostream>
#include <process.h>
#include "Common.h"
#include "WinSocketMain.h"
#include "ServerMain.h"
#include "User.h"


DWORD WINAPI WorkerThread(LPVOID arg);
DWORD WINAPI TimeWorkerThread(LPVOID arg);
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
		if (i != (int)si.dwNumberOfProcessors * 2 - 1)
		{
			hThread = (HANDLE)_beginthreadex(NULL, 0, (_beginthreadex_proc_type)WorkerThread, hcp, 0, NULL);
		}
		else
		{
			hThread = (HANDLE)_beginthreadex(NULL, 0, (_beginthreadex_proc_type)TimeWorkerThread, 0, 0, NULL);
		}
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
			Server->EraseSocket(client_sock);
			printf("[TCP 서버] 클라이언트 종료 : IP 주소 = %s, 포트 번호 = %d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));		
			closesocket(client_sock);
			continue;
		}
		ZeroMemory(&ptr->overlapped, sizeof(ptr->overlapped));
		ptr->wsabuf.buf = ptr->buf;
		ptr->wsabuf.len = BUFSIZE;

		User * pUser = Server->GetUser(client_sock);

		while (true)
		{
			cout << "쓰레드 ID :" << this_thread::get_id() << endl;
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
		DWORD recvbytes;
		DWORD flags = 0;
		retval = WSARecv(client_sock, &ptr->wsabuf, 1,
			&recvbytes, &flags, &ptr->overlapped, NULL);
		if (retval == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSA_IO_PENDING) {
				err_display("WSARecv()");
			}
			continue;
		}
	}
	return 0;
}
DWORD WINAPI TimeWorkerThread(LPVOID arg)
{
	while (1)
	{
		static int i = 0;
		i++;
		if(Server != NULL)
			Server->IncreaseTime();
		Sleep(1000);
	}
	return 0;
}