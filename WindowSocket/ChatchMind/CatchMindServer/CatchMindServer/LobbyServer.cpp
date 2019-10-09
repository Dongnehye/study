#include "LobbyServer.h"
#include <iostream>

using namespace std;

#define LOBBYROOMINDEX 0

void LobbyServer::RoomInit()
{
	Room * pNew = new Room(gRoomIndex);
	MapRoom.insert(make_pair(gRoomIndex, pNew));
	gRoomIndex++;
}

void LobbyServer::CreateRoom(SOCKET sock)
{
	Room * pNew = new Room(gRoomIndex);
	MapRoom.insert(make_pair(gRoomIndex,pNew));
	MapRoom[gRoomIndex]->AddUser(sock, MapUser[sock]);
	gRoomIndex++;
}

LobbyServer::LobbyServer()
{
	gRoomIndex = 1;
	RoomInit();
}


LobbyServer::~LobbyServer()
{
}

int LobbyServer::GetUserSize()
{
	return MapUser.size();
}

void LobbyServer::AddUser(SOCKET sock, User * user)
{
	MapUser.insert(make_pair(sock, user));
}

void LobbyServer::SendCheat(SOCKET sock, char * Buf, int len)
{
	string StrCheat;
	PACKET_SEND_CHEAT packet;
	memcpy(&packet, Buf, len);
	packet.Buf[packet.StrLen] = '\0';
	StrCheat = " : ";
	StrCheat += packet.Buf;
	StrCheat.insert(0, MapUser[sock]->id);

	packet.RoomIndex = MapUser[sock]->RoomIndex;
	packet.StrLen = strlen(StrCheat.c_str());
	strcpy(packet.Buf, StrCheat.c_str());
	packet.header.wLen = sizeof(packet.header) + sizeof(int) + sizeof(int) + sizeof(char) * strlen(StrCheat.c_str());

	for (auto iter = MapUser.begin(); iter != MapUser.end(); ++iter)
	{
		if (iter->second->RoomIndex == packet.RoomIndex)
		{
			send(iter->first, (const char*)&packet, packet.header.wLen, 0);
		}
	}
}

void LobbyServer::SendLobbyData(SOCKET sock)
{
	PACKET_LOBBY_REFRESH packet;
	packet.header.wIndex = PACKET_INDEX_SEND_LOBBY;
	packet.header.wLen = sizeof(packet.header) +
		(sizeof(LOBBY_DATA::RoomIndex) + sizeof(LOBBY_DATA::UserSize) + sizeof(LOBBY_DATA::IsStart) 
			+ sizeof(char) * SHORT_BUFSIZE + sizeof(char) * SHORT_BUFSIZE) * MapRoom.size() 
		+ sizeof(PACKET_LOBBY_REFRESH::LobbySize);
	int i = 0;
	for (auto iter = MapRoom.begin(); iter != MapRoom.end(); ++iter,++i)
	{
		strcpy(packet.data[i].Hostid, iter->second->HostId);
		strcpy(packet.data[i].Title, iter->second->RoomName);
		packet.data[i].IsStart = iter->second->IsStart;
		packet.data[i].RoomIndex = iter->second->index;
		packet.data[i].UserSize = iter->second->MapUser.size();
	}
	packet.LobbySize = MapRoom.size();

	send(sock, (const char*)&packet, packet.header.wLen, 0);
}

void LobbyServer::SendUserData(SOCKET sock)
{
	PACKET_ROOM_ALLUSER packet;
	packet.header.wIndex = PACKET_INDEX_SEND_ALLUSER;
	packet.header.wLen = sizeof(packet.header) +
		(sizeof(PACKET_ROOM_ALLUSER::MyIndex) + sizeof(PACKET_ROOM_ALLUSER::UserSize)
			+ sizeof(char) * SHORT_BUFSIZE) * MapUser.size();
	int i = 0;
	for (auto iter = MapUser.begin(); iter != MapUser.end(); ++iter, ++i)
	{
		packet.data[i].index = iter->second->Index;
		packet.data[i].CharacterIndex = iter->second->CharacterIndex;
		strcpy(packet.data[i].id, iter->second->id);
	}
	packet.UserSize = MapUser.size();
	packet.MyIndex = MapUser[sock]->Index;

	send(sock, (const char*)&packet, packet.header.wLen, 0);
}

void LobbyServer::SendRoomUserData(SOCKET sock)
{
	Room * pRoom = MapRoom[MapUser[sock]->RoomIndex];
	pRoom->SendUserData(sock);
}

void LobbyServer::AllSendUserData(SOCKET sock)
{
	PACKET_ROOM_USER packet;
	packet.header.wIndex = PACKET_INDEX_SEND_USER;
	packet.header.wLen = sizeof(packet.header) +
		(sizeof(PACKET_ROOM_USER::MyIndex) + sizeof(char) * SHORT_BUFSIZE);

	packet.data.index = MapUser[sock]->Index;
	packet.data.CharacterIndex = MapUser[sock]->CharacterIndex;
	strcpy(packet.data.id, MapUser[sock]->id);
	packet.MyIndex = MapUser[sock]->Index;

	for (auto iter = MapUser.begin(); iter != MapUser.end(); ++iter)
	{
		if(iter->first != sock)
			send(iter->first, (const char*)&packet, packet.header.wLen, 0);
	}
}

void LobbyServer::SendRoomEnter(SOCKET sock, char * Buf, int len)
{
	PACKET_SEND_ENTER_ROOM packet;
	memcpy(&packet, Buf, len);

	MapUser[sock]->RoomIndex = packet.RoomIndex;
	Room * pRoom = MapRoom[packet.RoomIndex];
	if (pRoom->AddUser(sock, MapUser[sock]))
	{
		cout << pRoom->index << ": 접속완료" << sock << endl;
	}
	else
	{
		cout << pRoom->index << ": 접속실패" << sock << endl;
	}
	packet.RoomIndex = pRoom->index;
	send(sock, Buf, len, 0);

	pRoom->AllSendUserData(sock);
}

void LobbyServer::CheckRoomReady(SOCKET sock, char * Buf, int len)
{

}

void LobbyServer::DisconnectPlayer(SOCKET sock)
{
	/*MapRoom[MapUser[sock]->RoomIndex]->DisconnectPlayer(sock);
	MapRoom[MapUser[sock]->RoomIndex]->UserSIze -= 1;*/
	MapUser.erase(sock);
}

void LobbyServer::ExitPlayer(SOCKET sock)
{
	//MapRoom[MapUser[sock]->RoomIndex]->
}

void LobbyServer::ProcessPacket(SOCKET sock, User * pUser,DWORD PacketIndex)
{
	switch (PacketIndex)
	{
	case PACKET_INDEX_SEND_CHEAT:
	{
		SendCheat(sock, pUser->buf, pUser->len);
	}
	break;
	case PACKET_INDEX_SEND_LOBBY:
	{
		SendLobbyData(sock);
		AllSendUserData(sock);
	}
	break;	
	case PACKET_INDEX_SEND_ALLUSER:
	{
		SendUserData(sock);
	}
	break;
	case PACKET_INDEX_SEND_ENTER_ROOM:
	{
		SendRoomEnter(sock, pUser->buf, pUser->len);
	}
	break;	
	case PACKET_INDEX_SEND_ROOM_ALLUSER:
	{
		SendRoomUserData(sock);
	}
	break;
	case PACKET_INDEX_SEND_EXIT_ROOM:
	{
		ExitPlayer(sock);
	}
	break;
	}
}
