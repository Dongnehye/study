#pragma comment(lib, "ws2_32")//라이브러리를 링크.
#include <WinSock2.h> // 윈속 라이브러리.
#include <stdlib.h>
#include <stdio.h>

#define SERVERPORT 9000 // 포트번호.
#define BUFSIZE	512

// 서버에서는 에러 메시지를 잘관리해야한다.
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
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) // 라이브러리 초기화. 2,2는 윈속 2.2버전을 쓰겠다는 뜻.
		return 1;

	// 접속 대기용 소켓.
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0); // AF_INET : ip4를 쓰겠다.
	if (sock == INVALID_SOCKET)
		err_quit("socket()");

	SOCKADDR_IN serveraddr; // 쌩 바이트다. SOCKADDR보다 구조적으로 잘되어있다.
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); // htonl 변환 함수. 아이피 주소 세팅.
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
		retval = recvfrom(sock,buf,BUFSIZE,0, (SOCKADDR*)&clientaddr, &addrlen); // 대기 상태, 접속할 경우에 진행한다.
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