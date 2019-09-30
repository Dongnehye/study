#include "LobbyServer.h"



void LobbyServer::RoomInit()
{
	for (int i = 1; i <= ROOMSIZE; ++i)
	{
		GameTable * pGameTableNew = new GameTable();
		pGameTableNew->Index = i;
		mapRoom.insert(make_pair(i, pGameTableNew));
	}
}

LobbyServer::LobbyServer()
{
	Index = 0;
	RoomInit();
}


LobbyServer::~LobbyServer()
{
}

int LobbyServer::GetUserSize()
{
	return mapUser.size();
}

void LobbyServer::AddUser(SOCKET sock, User * user)
{
	user->index = Index++;
	mapUser.insert(make_pair(sock, user));
}

void LobbyServer::SendLobbyData(SOCKET sock)
{
	PACKET_SEND_LOBBYDATA Lobbypacket;
	Lobbypacket.header.wIndex = PACKET_INDEX_SEND_LOBBY;
	Lobbypacket.header.wLen = sizeof(PACKET_HEADER) + sizeof(WORD) + sizeof(LOBBY_DATA) * mapRoom.size();
	Lobbypacket.LobbySize = mapRoom.size();

	printf("[TCP 서버] 로비 정보 : 로비 접속자 = %d \n",
		GetUserSize());
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

void LobbyServer::SendRoomEnter(SOCKET sock, char * Buf, int len)
{
	PACKET_SEND_ROOMENTER packet;
	memcpy(&packet, Buf, len);

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

void LobbyServer::CheckRoomReady(SOCKET sock, char * Buf, int len)
{
	PACKET_SEND_READY packet;
	memcpy(&packet, Buf, len);

	int RoomIndex = mapUser[sock]->RoomIndex;
	mapUser[sock]->IsReady = packet.IsReady;

	int ReadySIze = 0;
	for (auto iter = mapUser.begin(); iter != mapUser.end(); ++iter)
	{
		if (iter->second->RoomIndex == RoomIndex)
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
			if (iter->second->RoomIndex == RoomIndex)
			{
				send(iter->first, (const char*)&GameStartPacket, GameStartPacket.header.wLen, 0);
			}
		}
	}
}

void LobbyServer::SendCardRefresh(SOCKET sock, User * pUser)
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

void LobbyServer::SendAllCardRefresh(SOCKET sock, User * pUser)
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

void LobbyServer::SendBetting(SOCKET sock, char * Buf, int len)
{
	PACKET_SEND_BATTING packet;
	memcpy(&packet, Buf, len);

	auto Room = mapRoom[mapUser[sock]->RoomIndex];
	Room->Batting(mapUser[sock]->index, mapUser[sock], packet.BATTING);

	PACKET_SEND_BATTING_RES ResPacket;
	ResPacket.header.wIndex = PACKET_INDEX_SEND_BETTING;
	ResPacket.header.wLen = sizeof(ResPacket.header) + sizeof(int) + sizeof(WORD) + sizeof(int) + sizeof(int);
	ResPacket.Index = mapUser[sock]->index;
	ResPacket.BATTING = mapUser[sock]->BatState;
	ResPacket.Money = mapUser[sock]->Money;
	ResPacket.TotalMoney = Room->TotalMoney;

	for (auto iter = mapUser.begin(); iter != mapUser.end(); ++iter)
	{
		if (iter->second->RoomIndex == Room->Index)
		{
			send(sock, (const char *)&ResPacket, ResPacket.header.wLen, 0);
		}
	}
}

void LobbyServer::SendExchange(SOCKET sock, char * Buf, int len)
{
	PACKET_SEND_EXCHANGE packet;
	memcpy(&packet, Buf, len);

	auto Room = mapRoom[mapUser[sock]->RoomIndex];
	Room->CardChange(mapUser[sock]->index, mapUser[sock], packet.Card);

	SendAllCardRefresh(sock, mapUser[sock]);
}

void LobbyServer::SendTurnRespond(SOCKET sock, char * Buf, int len)
{
	PACKET_HEADER ResPacket;
	memcpy(&ResPacket, Buf, len);

	auto Room = mapRoom[mapUser[sock]->RoomIndex];

	int Turn = Room->CheckNextTurn(mapUser[sock]->index);

	PACKET_SEND_TURN RetPacket;
	RetPacket.header.wIndex = PACKET_INDEX_SEND_TURN;
	RetPacket.header.wLen = sizeof(RetPacket.header) + sizeof(int) + sizeof(WORD);
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
