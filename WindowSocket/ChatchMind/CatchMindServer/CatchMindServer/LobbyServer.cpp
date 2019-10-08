#include "LobbyServer.h"
#include <iostream>

using namespace std;

#define LOBBYROOMINDEX 0

void LobbyServer::RoomInit()
{

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
	gRoomIndex = 0;
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
	}
}
