#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include "PACKET_HEADER.H"
#include "CommonHeader.h"
#include "User.h"
#include "Room.h"

using namespace std;


#define WM_SOCKET (WM_USER+1)

int g_iIndex = 0;
map<SOCKET, User*> g_mapUser;
vector<Room*> VecRoom;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void ProcessSocketMessage(HWND, UINT, WPARAM, LPARAM);
bool ProcessPacket(SOCKET sock, User* pUser, char* szBuf, int& len);
bool CheckLogin(const char * Id, const char * pw, int &Money);

void err_display(int errcode);
void err_display(const char* szMsg);

int main(int argc, char* argv[])
{
	int retval;

	WNDCLASS WndClass;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = NULL;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = "WSAAsyncSelectServer";
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	if (!RegisterClass(&WndClass))
		return -1;

	HWND hWnd = CreateWindow("WSAAsyncSelectServer", "TCP ����", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		100, 100, NULL, (HMENU)NULL, NULL, NULL);
	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return -1;

	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET)
	{
		cout << "err on socket" << endl;
		return -1;
	}

	retval = WSAAsyncSelect(listen_sock, hWnd, WM_SOCKET, FD_ACCEPT | FD_CLOSE);
	if (retval == SOCKET_ERROR)
	{
		cout << "err on WSAAsyncSelect" << endl;
		return -1;
	}

	//bind
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(9000);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	retval = bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR)
	{
		cout << "err on bind" << endl;
		return -1;
	}

	//listen
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR)
	{
		cout << "err on listen" << endl;
		return -1;
	}
	//RoomInit
	for (int i = 0; i < ROOMSIZE; ++i)
	{
		Room * pNew = new Room();
		VecRoom.push_back(pNew);
	}

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_SOCKET:
		ProcessSocketMessage(hWnd, uMsg, wParam, lParam);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void ProcessSocketMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen = 0;
	int retval = 0;


	if (WSAGETSELECTERROR(lParam))
	{
		int err_code = WSAGETSELECTERROR(lParam);
		err_display(WSAGETSELECTERROR(lParam));
		return;
	}

	switch (WSAGETSELECTEVENT(lParam))
	{
	case FD_ACCEPT:
	{
		addrlen = sizeof(clientaddr);
		client_sock = accept(wParam, (SOCKADDR*)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET)
		{
			int err_code = WSAGetLastError();
			if (err_code != WSAEWOULDBLOCK)
			{
				err_display("err on accept");
			}
			return;
		}
		printf("[TCP ����] Ŭ���̾�Ʈ ���� : IP �ּ� = %s , ��Ʈ��ȣ = %d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		retval = WSAAsyncSelect(client_sock, hWnd, WM_SOCKET, FD_READ | FD_CLOSE);
		if (retval == SOCKET_ERROR)
		{
			cout << "err on WSAAsyncSelect!!" << endl;
		}
		User* pInfo = new User();
		pInfo->index = g_iIndex++;
		pInfo->len = 0;
		g_mapUser.insert(make_pair(client_sock, pInfo));

		//PACKET_LOGIN_RET packet;
		//packet.header.wIndex = PACKET_INDEX_LOGIN_RET;
		//packet.header.wLen = sizeof(packet);
		//packet.iIndex = pInfo->index;
		//send(client_sock, (const char*)&packet, packet.header.wLen, 0);

		//Sleep(500);

		//PACKET_USER_DATA user_packet;
		//user_packet.header.wIndex = PACKET_INDEX_USER_DATA;
		//user_packet.header.wLen = sizeof(PACKET_HEADER) + sizeof(WORD) + sizeof(USER_DATA) * g_mapUser.size();
		//user_packet.wCount = g_mapUser.size();
		//
		//
		//int i = 0;
		//for (auto iter = g_mapUser.begin(); iter != g_mapUser.end(); iter++, i++)
		//{
		//	user_packet.data[i].iIndex = iter->second->index;
		//}

		//for (auto iter = g_mapUser.begin(); iter != g_mapUser.end(); iter++, i++)
		//{
		//	send(iter->first, (const char*)&user_packet, user_packet.header.wLen, 0);
		//}
	}
	break;
	case FD_READ:
	{
		char szBuf[BUFSIZE];

		retval = recv(wParam, szBuf, BUFSIZE, 0);
		if (retval == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				cout << "err on recv!!" << endl;
			}
		}

		User* pUser = g_mapUser[wParam];

		while (true)
		{
			if (!ProcessPacket(wParam, pUser, szBuf, retval))
			{
				Sleep(100);
				//SendMessage(hWnd, uMsg, wParam, lParam);
				break;
			}
			else
			{
				if (pUser->len < sizeof(PACKET_HEADER))
					break;
			}
		}

	}
	break;
	case FD_CLOSE:
		for (auto iter = VecRoom.begin(); iter != VecRoom.end(); ++iter)
		{
			delete (*iter);
		}
		VecRoom.clear();

		closesocket(wParam);
		break;
	}
}

bool ProcessPacket(SOCKET sock, User* pUser, char* szBuf, int& len)
{
	if (len > 0)
	{
		memcpy(&pUser->szBuf[pUser->len], szBuf, len);
		pUser->len += len;
		len = 0;
	}

	if (pUser->len < sizeof(PACKET_HEADER))
		return false;

	PACKET_HEADER header;
	memcpy(&header, pUser->szBuf, sizeof(header));

	if (pUser->len < header.wLen)
		return false;

	switch (header.wIndex)
	{
	case PACKET_INDEX_LOGIN_RET:
	{
		PACKET_LOGIN_RET packet;
		memcpy(&packet, szBuf, header.wLen);
		// �α��� �˻�.
		int Money = 0;

		if (CheckLogin((const char*)packet.Id, (const char*)packet.Pw,Money))
		{
			printf("[TCP ����] Ŭ���̾�Ʈ ���� : ID = %s , PW = %s, Money = %d\n", 
				(const char*)packet.Id, (const char*)packet.Pw, Money);
		}

		//PACKET_USER_DATA user_packet;
		//user_packet.header.wIndex = PACKET_INDEX_USER_DATA;
		//user_packet.header.wLen = sizeof(PACKET_HEADER) + sizeof(WORD) + sizeof(USER_DATA) * g_mapUser.size();
		//user_packet.wCount = g_mapUser.size();
		//
		//
		//int i = 0;
		//for (auto iter = g_mapUser.begin(); iter != g_mapUser.end(); iter++, i++)
		//{
		//	user_packet.data[i].iIndex = iter->second->index;
		//}

		//for (auto iter = g_mapUser.begin(); iter != g_mapUser.end(); iter++, i++)
		//{
		//	send(iter->first, (const char*)&user_packet, user_packet.header.wLen, 0);
		//}

	}
	break;
	case PACKET_INDEX_SEND_POS:
	{
		PACKET_SEND_POS packet;
		memcpy(&packet, szBuf, header.wLen);

		//g_mapUser[sock]->x = packet.data.wX;
		//g_mapUser[sock]->y = packet.data.wY;

		for (auto iter = g_mapUser.begin(); iter != g_mapUser.end(); iter++)
		{
			//if (iter->first == sock)
				//continue;

			send(iter->first, (const char*)&packet, header.wLen, 0);
		}
	}
	break;
	}

	memcpy(&pUser->szBuf, &pUser->szBuf[header.wLen], pUser->len - header.wLen);
	pUser->len -= header.wLen;

	return true;
}
bool CheckLogin(const char * Id, const char * pw,int &Money)
{
	ifstream in("DataBase.txt");
	string StrId;
	string StrPw;
	int IMoney;

	if (!in.is_open())
	{
		return false;
	}
	else
	{
		while (in)
		{
			in >> StrId;
			in >> StrPw;

			if (strcmp(StrId.c_str(), Id) == 0
				&& strcmp(StrPw.c_str(), pw) == 0)
			{
				Money = IMoney;
				return true;
			}
			in >> IMoney;
		}
	}
	return false;
}

void err_display(int errcode)
{
	LPVOID lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[����]%s", lpMsgBuf);
	LocalFree(lpMsgBuf);
}

void err_display(const char* szMsg)
{
	LPVOID lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s]%s\n", szMsg, lpMsgBuf);
	LocalFree(lpMsgBuf);
}