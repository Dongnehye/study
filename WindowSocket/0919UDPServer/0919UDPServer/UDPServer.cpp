#pragma comment(lib, "ws2_32")//���̺귯���� ��ũ.
#include <WinSock2.h> // ���� ���̺귯��.
#include <stdlib.h>
#include <stdio.h>

#define SERVERPORT 9000 // ��Ʈ��ȣ.
#define BUFSIZE	512

// ���������� ���� �޽����� �߰����ؾ��Ѵ�.
void err_quit(const char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

void err_display(const char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

int main(int argc, char * argv[])
{
	int retval;

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) // ���̺귯�� �ʱ�ȭ. 2,2�� ���� 2.2������ ���ڴٴ� ��.
		return 1;

	// ���� ���� ����.
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0); // AF_INET : ip4�� ���ڴ�.
	if (sock == INVALID_SOCKET)
		err_quit("socket()");

	SOCKADDR_IN serveraddr; // �� ����Ʈ��. SOCKADDR���� ���������� �ߵǾ��ִ�.
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); // htonl ��ȯ �Լ�. ������ �ּ� ����.
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR)
		err_quit("bind()");

	SOCKADDR_IN clientaddr;
	int addrlen;
	char buf[BUFSIZE + 1];

	while (1)
	{
		addrlen = sizeof(clientaddr);
		retval = recvfrom(sock,buf,BUFSIZE,0, (SOCKADDR*)&clientaddr, &addrlen); // ��� ����, ������ ��쿡 �����Ѵ�.
		if (retval == SOCKET_ERROR)
		{
			err_display("recvfrom()");
			continue;
		}

		buf[retval] = '\0';
		printf("[UDP/%s:%d] %s\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port), buf);

		retval = sendto(sock, buf, retval, 0, (SOCKADDR*)&clientaddr, sizeof(clientaddr));
		if (retval == SOCKET_ERROR)
		{
			err_display("sendto()");
			continue;
		}
	}
	closesocket(sock);
	WSACleanup();
	return 0;

}