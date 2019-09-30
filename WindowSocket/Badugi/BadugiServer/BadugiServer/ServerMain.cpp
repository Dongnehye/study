#include "ServerMain.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;




ServerMain::ServerMain()
{
	Lobby = new LobbyServer();
}


ServerMain::~ServerMain()
{
	for (auto iter = mapUser.begin(); iter != mapUser.end(); ++iter)
	{
		delete iter->second;
	}
	mapUser.clear();
	delete Lobby;
}

void ServerMain::ProcessSocketMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
		printf("[TCP 서버] 클라이언트 접속 : IP 주소 = %s , 포트번호 = %d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		retval = WSAAsyncSelect(client_sock, hWnd, WM_SOCKET, FD_READ | FD_CLOSE);
		if (retval == SOCKET_ERROR)
		{
			cout << "err on WSAAsyncSelect!!" << endl;
		}
		AddUser(client_sock);
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

		User* pUser = mapUser[wParam];

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
		closesocket(wParam);
		break;
	}
}

bool ServerMain::ProcessPacket(SOCKET sock, User * pUser, char * szBuf, int & len)
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
		SendLogin(sock, szBuf, header.wLen);
	}
	break;
	case PACKET_INDEX_SEND_LOBBYREFRESH:
	{
		Lobby->SendLobbyData(sock);
	}
	break;
	case PACKET_INDEX_SEND_ROOMENTER:
	{
		Lobby->SendRoomEnter(sock, szBuf, header.wLen);
	}
	break;
	case PACKET_INDEX_SEND_READY:
	{
		Lobby->CheckRoomReady(sock, szBuf, header.wLen);
	}
	break;
	case PACKET_INDEX_SEND_CARD:
	{
		Lobby->SendCardRefresh(sock, pUser);
	}
	break;
	case PACKET_INDEX_SEND_BETTING:
	{
		Lobby->SendBetting(sock, szBuf, header.wLen);
	}
	break;
	case PACKET_INDEX_SEND_EXCHANGE:
	{
		Lobby->SendExchange(sock, szBuf, header.wLen);
	}
	break;
	case PACKET_INDEX_SEND_TURN_RESPOND:
	{
		Lobby->SendTurnRespond(sock, szBuf, header.wLen);
	}
	break;
	case PACKET_INDEX_SEND_CHAT:
	{
		PACKET_SEND_CHEAT packet;
		memcpy(&packet, szBuf, header.wLen);

		printf("%s", packet.Buf);

	}
	break;
	}
	memcpy(&pUser->szBuf, &pUser->szBuf[header.wLen], pUser->len - header.wLen);
	pUser->len -= header.wLen;

	return true;
}
void ServerMain::AddUser(SOCKET sock)
{
	User* pInfo = new User();
	pInfo->index = g_iIndex++;
	pInfo->len = 0;
	mapUser.insert(make_pair(sock, pInfo));
}

bool ServerMain::CheckLogin(const char * Id, const char * pw, int & Money)
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
			in >> IMoney;
			if (strcmp(StrId.c_str(), Id) == 0
				&& strcmp(StrPw.c_str(), pw) == 0)
			{
				Money = IMoney;
				return true;
			}
		}
	}
	return false;
}

void ServerMain::SendLogin(SOCKET sock, char * Buf, int len)
{
	PACKET_LOGIN_RET RetPacket;
	memcpy(&RetPacket, Buf, len);

	PACKET_LOGIN_RES ResPacket;
	ResPacket.header.wIndex = PACKET_INDEX_LOGIN_RES;
	ResPacket.header.wLen = sizeof(ResPacket);

	// 로그인 검사.
	int Money = 0;

	if (CheckLogin((const char*)RetPacket.Id, (const char*)RetPacket.Pw, Money))
	{
		printf("[TCP 서버] 클라이언트 접속 : ID = %s , PW = %s, Money = %d\n",
			(const char*)RetPacket.Id, (const char*)RetPacket.Pw, Money);
		ResPacket.IsLogin = true;

		strcpy(ResPacket.data.Id, (const char*)RetPacket.Id);
		strcpy(ResPacket.data.Pw, (const char*)RetPacket.Pw);

		ResPacket.data.Money = Money;
		ResPacket.data.iIndex = mapUser[sock]->index;

		mapUser[sock]->SceneIndex = SCENE_INDEX_LOBBY;
		strcpy(mapUser[sock]->Id, (const char*)RetPacket.Id);
		mapUser[sock]->Money = Money;

		Lobby->AddUser(sock, mapUser[sock]);
	}
	else
	{
		ResPacket.IsLogin = false;
		printf("[TCP 서버] 클라이언트 로그인 실패 : ID = %s , PW = %s\n",
			(const char*)RetPacket.Id, (const char*)RetPacket.Pw);
	}

	send(sock, (const char*)&ResPacket, ResPacket.header.wLen, 0);
}

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
