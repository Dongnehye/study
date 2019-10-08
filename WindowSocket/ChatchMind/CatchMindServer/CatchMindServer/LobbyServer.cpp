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
//(sizeof(USER_DATA::CharacterIndex) + sizeof(USER_DATA::index) + sizeof(char) * 20) * MapUser.size()
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
	PACKET_ROOM_USER packet;
	packet.header.wIndex = PACKET_INDEX_SEND_USER;
	packet.header.wLen = sizeof(packet.header) +
		(sizeof(PACKET_ROOM_USER::MyIndex) + sizeof(PACKET_ROOM_USER::UserSize)
			+ sizeof(char) * SHORT_BUFSIZE) * MapUser.size();
	int i = 0;
	for (auto iter = MapUser.begin(); iter != MapUser.end(); ++iter, ++i)
	{
		packet.User[i].index = iter->second->Index;
		packet.User[i].CharacterIndex = iter->second->CharacterIndex;
		strcpy(packet.User[i].id, iter->second->id);
	}
	packet.UserSize = MapUser.size();
	packet.MyIndex = MapUser[sock]->Index;

	send(sock, (const char*)&packet, packet.header.wLen, 0);
}

void LobbyServer::SendRoomEnter(SOCKET sock, char * Buf, int len)
{


}

void LobbyServer::CheckRoomReady(SOCKET sock, char * Buf, int len)
{

}

void LobbyServer::DisconnectPlayer(SOCKET sock)
{

}

void LobbyServer::ExitPlayer(SOCKET sock)
{

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
	}
	break;	
	case PACKET_INDEX_SEND_USER:
	{
		SendUserData(sock);
	}
	break;
	}
}
