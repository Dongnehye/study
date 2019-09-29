#include "ServerMain.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void ServerMain::RoomInit()
{
	mLobby = new Lobby();
	for (int i = 1; i <= ROOMSIZE; ++i)
	{
		GameTable * pGameTableNew = new GameTable();
		pGameTableNew->Index = i;
		mapRoom.insert(make_pair( i,pGameTableNew));
	}
}

void ServerMain::SendCardRefresh(SOCKET sock ,User * pUser)
{
	PACKET_SEND_CARD packetCard;
	packetCard.header.wIndex = PACKET_INDEX_SEND_CARD;
	packetCard.header.wLen = sizeof(PACKET_HEADER) + sizeof(USER_CARD_DATA) * ROOMPLAYERSIZE;

	int i = 0;
	for (auto iter = mapUser.begin(); iter != mapUser.end(); ++iter)
	{
		if (iter->second->RoomIndex == pUser->RoomIndex)
		{
			packetCard.data[i].iIndex = iter->second->index;
			int j = 0;
			for (auto iterCard = iter->second->card.begin(); iterCard != iter->second->card.end(); ++iterCard, ++j)
			{
				packetCard.data[i].Card[j] = (*iterCard);
			}
			++i;
		}
	}
	send(sock, (const char*)&packetCard, packetCard.header.wLen, 0);
}
void ServerMain::SendAllCardRefresh(SOCKET sock, User * pUser)
{
	PACKET_ALL_SEND_CARD packet;
	packet.header.wIndex = PACKET_INDEX_SEND_ALLCARD;
	packet.Index = pUser->index;
	packet.header.wLen = sizeof(PACKET_HEADER) + sizeof(int) + sizeof(USER_CARD_DATA) * ROOMPLAYERSIZE;

	int i = 0;
	for (auto iter = mapUser.begin(); iter != mapUser.end(); ++iter)
	{
		if (iter->second->RoomIndex == pUser->RoomIndex)
		{
			packet.data[i].iIndex = iter->second->index;
			int j = 0;
			for (auto iterCard = iter->second->card.begin(); iterCard != iter->second->card.end(); ++iterCard, ++j)
			{
				packet.data[i].Card[j] = (*iterCard);
			}
			++i;
		}
	}
	for (auto iter = mapUser.begin(); iter != mapUser.end(); ++iter)
	{
		if (iter->second->RoomIndex == pUser->RoomIndex)
		{
			send(iter->first, (const char*)&packet, packet.header.wLen, 0);
		}
	}
}

ServerMain::ServerMain()
{
	RoomInit();
}


ServerMain::~ServerMain()
{
	for (auto iter = mapRoom.begin(); iter != mapRoom.end(); ++iter)
	{
		delete iter->second;
	}
	mapRoom.clear();
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
		mapUser.insert(make_pair(client_sock, pInfo));

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

			mapUser[sock]->SceneIndex = SCENE_INDEX_LOBBY;
			strcpy(mapUser[sock]->Id, (const char*)RetPacket.Id);
			mapUser[sock]->Money = Money;
		}
		else
		{
			ResPacket.IsLogin = false;
			printf("[TCP 서버] 클라이언트 로그인 실패 : ID = %s , PW = %s\n",
				(const char*)RetPacket.Id, (const char*)RetPacket.Pw);
		}

		send(sock, (const char*)&ResPacket, ResPacket.header.wLen, 0);
	}
	break;
	case PACKET_INDEX_SEND_LOBBYREFRESH:
	{
		PACKET_SEND_LOBBYDATA Lobbypacket;
		Lobbypacket.header.wIndex = PACKET_INDEX_SEND_LOBBY;
		Lobbypacket.header.wLen = sizeof(PACKET_HEADER) + sizeof(WORD) + sizeof(LOBBY_DATA) * mapRoom.size();
		Lobbypacket.LobbySize = mapRoom.size();

		printf("[TCP 서버] 로비 정보 : 로비 접속자 = %d \n",
			mLobby->GetUserSize());
		int i = 1;
		for (auto iter = mapRoom.begin(); iter != mapRoom.end(); ++iter, ++i)
		{
			printf("[TCP 서버] 클라이언트 방 정보 : RoomIndex = %d, 방접속자 = %d \n",
				i, iter->second->GetUserSize());
		}

		i = 0;
		for (auto iter = mapRoom.begin(); iter != mapRoom.end(); ++iter, ++i)
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
		if (mapUser[sock]->SceneIndex == SCENE_INDEX_LOBBY)
		{
			if (mapRoom[WantRoomIndex]->UserSIze < ROOMPLAYERSIZE)
			{
				mapUser[sock]->RoomIndex = packet.RoomIndex;
				mapUser[sock]->SceneIndex = SCENE_INDEX_ROOM;
				printf("[TCP 서버] 클라이언트 방 접속 : RoomIndex = %d\n",
					mapUser[sock]->RoomIndex);
				IsRoomEnter = true;

				PACKET_SEND_ROOMENTER_RES packet;
				packet.header.wIndex = PACKET_INDEX_SEND_ROOMENTER_RES;
				packet.header.wLen = sizeof(PACKET_HEADER) + sizeof(WORD) +
					sizeof(USER_ROOM_DATA) * ROOMPLAYERSIZE + sizeof(int) + sizeof(bool);
				packet.RoomIndex = mapUser[sock]->RoomIndex;
				packet.isRoomEnter = IsRoomEnter;

				if (mapRoom[WantRoomIndex]->UserSIze == 0)
					mapUser[sock]->IsHost = true;
				else
					mapUser[sock]->IsHost = false;
				int i = 0;
				for (auto iter = mapUser.begin(); iter != mapUser.end(); ++iter)
				{
					if (iter->second->RoomIndex == WantRoomIndex)
					{
						packet.data[i].iIndex = iter->second->index;
						strcpy(packet.data[i].Id, iter->second->Id);
						packet.data[i].Money = iter->second->Money;
						packet.data[i].IsHost = iter->second->IsHost;
						++i;
					}
				}
				packet.UserSize = i;
				for (auto iter = mapUser.begin(); iter != mapUser.end(); ++iter)
				{
					if (iter->second->RoomIndex == WantRoomIndex)
					{
						send(iter->first, (const char*)&packet, packet.header.wLen, 0);
					}
				}

				mapRoom[WantRoomIndex]->UserSIze += 1;

			}
			else
			{
				printf("[TCP 서버] 클라이언트 방 접속실패 : RoomIndex = %d 인원수 초과\n",
					WantRoomIndex);
				IsRoomEnter = false;
				// ERRor message
				//send(sock, (const char*)&packet, packet.header.wLen, 0);
			}
		}
	}
	break;
	case PACKET_INDEX_SEND_READY:
	{
		PACKET_SEND_READY packet;
		memcpy(&packet, szBuf, header.wLen);

		int RoomIndex = mapUser[sock]->RoomIndex;
		mapUser[sock]->IsReady = packet.IsReady;

		int ReadySIze = 0;
		for (auto iter = mapUser.begin(); iter != mapUser.end(); ++iter)
		{
			if (iter->second->RoomIndex == pUser->RoomIndex)
			{
				if (iter->second->IsReady)
				{
					++ReadySIze;
				}
			}
		}
		if (ReadySIze >= ROOMPLAYERSIZE)
		{
			mapRoom[RoomIndex]->GameStart(mapUser);
			PACKET_SEND_GAMESTART GameStartPacket;
			GameStartPacket.header.wIndex = PACKET_INDEX_SEND_GAMESTART;
			GameStartPacket.header.wLen = sizeof(GameStartPacket.header) + sizeof(int);
			GameStartPacket.FirstTurnIndex = mapRoom[RoomIndex]->TurnPlayerIndex;

			for (auto iter = mapUser.begin(); iter != mapUser.end(); ++iter)
			{
				if (iter->second->RoomIndex == pUser->RoomIndex)
				{
					send(iter->first, (const char*)&GameStartPacket, GameStartPacket.header.wLen, 0);
				}
			}
		}
	}
	break;
	case PACKET_INDEX_SEND_CARD:
	{
		PACKET_SEND_TURN packet;
		memcpy(&packet, szBuf, header.wLen);

		SendCardRefresh(sock, pUser);

	}
	break;
	case PACKET_INDEX_SEND_BETTING:
	{
		PACKET_SEND_BATTING packet;
		memcpy(&packet, szBuf, header.wLen);

		auto Room = mapRoom[mapUser[sock]->RoomIndex];
		Room->Batting(mapUser[sock]->index, mapUser[sock], packet.BATTING);

		PACKET_SEND_BATTING_RES ResPacket;
		ResPacket.header.wIndex = PACKET_INDEX_SEND_BETTING;
		ResPacket.header.wLen = sizeof(ResPacket.header) + sizeof(int) + sizeof(WORD) + sizeof(int) + sizeof(int);
		ResPacket.Index = mapUser[sock]->index;
		ResPacket.BATTING = mapUser[sock]->BatState;
		ResPacket.Money = pUser->Money;
		ResPacket.TotalMoney = Room->TotalMoney;

		for (auto iter = mapUser.begin(); iter != mapUser.end(); ++iter)
		{
			if (iter->second->RoomIndex == Room->Index)
			{
				send(sock, (const char *)&ResPacket, ResPacket.header.wLen, 0);
			}
		}
	}
	break;
	case PACKET_INDEX_SEND_EXCHANGE:
	{
		PACKET_SEND_EXCHANGE packet;
		memcpy(&packet, szBuf, header.wLen);

		auto Room = mapRoom[mapUser[sock]->RoomIndex];
		Room->CardChange(mapUser[sock]->index, mapUser[sock], packet.Card);

		SendAllCardRefresh(sock, pUser);
	}
	break;
	case PACKET_INDEX_SEND_TURN_RESPOND:
	{
		PACKET_HEADER ResPacket;
		memcpy(&ResPacket, szBuf, header.wLen);

		auto Room = mapRoom[mapUser[sock]->RoomIndex];

		int Turn = Room->CheckNextTurn(mapUser[sock]->index);

		PACKET_SEND_TURN RetPacket;
		RetPacket.header.wIndex = PACKET_INDEX_SEND_TURN;
		RetPacket.header.wLen = sizeof(RetPacket.header) + sizeof(int) +sizeof(WORD);
		RetPacket.TURN = Turn;

		int NextPalyerIndex = Room->GetNextPlayerIndex();

		for (auto iter = mapUser.begin(); iter != mapUser.end(); ++iter)
		{
			if (iter->second->RoomIndex == Room->Index)
			{
				RetPacket.Index = NextPalyerIndex;
				send(iter->first, (const char*)&RetPacket, RetPacket.header.wLen, 0);
			}
		}
	}
	break;
	}
	memcpy(&pUser->szBuf, &pUser->szBuf[header.wLen], pUser->len - header.wLen);
	pUser->len -= header.wLen;

	return true;
}

void ServerMain::SwitchPacket(SOCKET sock, User * pUser, char * szBuf, int & len, WORD Index)
{
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
