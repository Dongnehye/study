#include "ServerMain.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void ServerMain::RoomInit()
{
	//for (int i = 0; i < ROOMSIZE; ++i)
	//{
	//	Room * pNew = new Room();
	//	VecRoom.push_back(pNew);
	//}
	mLobby = new Lobby();
	mLobby->UserSIze = 8;
	for (int i = 1; i <= ROOMSIZE; ++i)
	{
		GameTable * pGameTableNew = new GameTable();

		if (i == 8)
			pGameTableNew->UserSIze = 0;
		else
			pGameTableNew->UserSIze = 4;

		VecRoom.insert(make_pair( i,pGameTableNew));
	}

}

ServerMain::ServerMain()
{
	RoomInit();
}


ServerMain::~ServerMain()
{
	for (auto iter = VecRoom.begin(); iter != VecRoom.end(); ++iter)
	{
		delete iter->second;
	}
	VecRoom.clear();
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
		PACKET_LOGIN_RET RetPacket;
		memcpy(&RetPacket, szBuf, header.wLen);

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
			ResPacket.data.iIndex = pUser->index;

			g_mapUser[sock]->SceneIndex = SCENE_INDEX_LOBBY;
			strcpy(g_mapUser[sock]->Id, (const char*)RetPacket.Id);
			g_mapUser[sock]->Money = Money;
		}
		else
		{
			ResPacket.IsLogin = false;
			printf("[TCP 서버] 클라이언트 로그인 실패 : ID = %s , PW = %s\n",
				(const char*)RetPacket.Id, (const char*)RetPacket.Pw);
		}

		send(sock, (const char*)&ResPacket, ResPacket.header.wLen, 0);

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
	case PACKET_INDEX_SEND_LOBBYREFRESH:
	{
		PACKET_SEND_LOBBYDATA Lobbypacket;
		Lobbypacket.header.wIndex = PACKET_INDEX_SEND_LOBBY;
		Lobbypacket.header.wLen = sizeof(PACKET_HEADER) + sizeof(WORD) + sizeof(LOBBY_DATA) * VecRoom.size();
		Lobbypacket.LobbySize = VecRoom.size();

		printf("[TCP 서버] 로비 정보 : 로비 접속자 = %d \n",
			mLobby->GetUserSize());
		int i = 1;
		for (auto iter = VecRoom.begin(); iter != VecRoom.end(); ++iter, ++i)
		{
			printf("[TCP 서버] 클라이언트 방 정보 : RoomIndex = %d, 방접속자 = %d \n",
					i, iter->second->GetUserSize());	
		}

		i = 0;
		for (auto iter = VecRoom.begin(); iter != VecRoom.end(); ++iter, ++i)
		{
			Lobbypacket.data[i].iIndex = 1 + i;
			Lobbypacket.data[i].IsStart = false;
			Lobbypacket.data[i].UserSize = iter->second->GetUserSize();
		}

		send(sock, (const char*)&Lobbypacket, Lobbypacket.header.wLen, 0);
	}
	break;
	case PACKET_INDEX_SEND_ROOMENTER:
	{
		PACKET_SEND_ROOMENTER packet;
		memcpy(&packet, szBuf, header.wLen);

		int WantRoomIndex = packet.RoomIndex;
		bool IsRoomEnter = false;
		if (g_mapUser[sock]->SceneIndex == SCENE_INDEX_LOBBY)
		{
			if (VecRoom[WantRoomIndex]->UserSIze < ROOMPLAYERSIZE)
			{
				g_mapUser[sock]->RoomIndex = packet.RoomIndex;
				printf("[TCP 서버] 클라이언트 방 접속 : RoomIndex = %d\n",
					g_mapUser[sock]->RoomIndex);
				IsRoomEnter = true;
			}
			else
			{
				printf("[TCP 서버] 클라이언트 방 접속실패 : RoomIndex = %d 인원수 초과\n",
					WantRoomIndex);
				IsRoomEnter = false;
			}

			PACKET_SEND_ROOMENTER_RES packet;
			packet.header.wIndex = PACKET_INDEX_SEND_ROOMENTER_RES;
			packet.header.wLen = sizeof(PACKET_HEADER) + sizeof(WORD) + sizeof(bool);
			packet.RoomIndex = g_mapUser[sock]->RoomIndex;
			packet.isRoomEnter = IsRoomEnter;
			send(sock, (const char*)&packet, packet.header.wLen, 0);
		}
	}
	break;
	}

	memcpy(&pUser->szBuf, &pUser->szBuf[header.wLen], pUser->len - header.wLen);
	pUser->len -= header.wLen;

	return true;
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
