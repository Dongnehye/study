#include "Room.h"
#include <iostream>

Room::Room()
{

}


Room::Room(int _index)
{
	index = _index;
	strcpy(RoomName, "한수");
	strcpy(HostId, "기본");
	IsStart = false;
}

Room::~Room()
{
}

bool Room::AddUser(SOCKET sock, User * pUser)
{
	MapUser.insert(make_pair(sock, pUser));
	pUser->RoomIndex = index;

	int i = 0;
	for (; i < MapUser.size(); ++i)
	{
		if (UserOrder.find(i) == UserOrder.end())
		{
			UserOrder.insert(make_pair(i, sock));
			MapUser[sock]->MyIndexRoom = i;
			return true;
		}
	}
	UserOrder.insert(make_pair(i, sock));

	return true;
}

bool Room::ExitUser(SOCKET sock, User * pUser)
{
	if (MapUser.find(sock) != MapUser.end())
	{
		MapUser[sock]->RoomIndex = LOBBYINDEX;
		UserOrder.erase(MapUser[sock]->MyIndexRoom);
		MapUser.erase(sock);

		PACKET_SEND_EXIT_ROOM packet;
		packet.header.wIndex = PACKET_INDEX_SEND_EXIT_ROOM;
		packet.header.wLen = sizeof(packet);
		packet.Index = pUser->MyIndexRoom;
		send(sock, (const char*)&packet, packet.header.wLen, 0);

		packet.header.wIndex = PACKET_INDEX_SEND_OTHER_EXIT_ROOM;
		
		for (auto iter = MapUser.begin(); iter != MapUser.end(); ++iter)
		{
			if (iter->first != sock)
				send(iter->first, (const char*)&packet, packet.header.wLen, 0);
		}	
		return true;
	}
	return false;
}

void Room::AddLine(int x0, int y0, int x1, int y1, int Color)
{
	DRAWLINE Line;
	Line.x0 = x0;
	Line.x1 = x1;
	Line.y0 = y0;
	Line.y1 = y1;
	Line.color = Color;
	VecLine.push_back(Line);
	cout << VecLine.size() << endl;
}

void Room::EchoLine(SOCKET sock, DRAWLINE Line)
{
	PACKET_SEND_DRAW_LINE packet;
	packet.header.wIndex = PACKET_INDEX_SEND_DRAW_LINE;
	packet.header.wLen = sizeof(packet);
	packet.data = Line;
	packet.Index = MapUser[sock]->MyIndexRoom;

	for (auto iter = MapUser.begin(); iter != MapUser.end(); ++iter)
	{
		if (iter->first != sock)
			send(iter->first, (const char*)&packet, packet.header.wLen, 0);
	}
}

void Room::ClearLine(SOCKET sock)
{
	VecLine.clear();
	
	PACKET_USER_REQUEST packet;
	packet.header.wIndex = PACKET_INDEX_SEND_DRAW_CLEAR;
	packet.header.wLen = sizeof(packet);
	for (auto iter = MapUser.begin(); iter != MapUser.end(); ++iter)
	{
			send(iter->first, (const char*)&packet, packet.header.wLen, 0);
	}
}

void Room::SendUserData(SOCKET sock)
{
	int UserSize = MapUser.size();

	PACKET_SEND_ENTER_ROOM_RES packet;
	packet.header.wIndex = PACKET_INDEX_SEND_ALLUSER;
	packet.header.wLen = sizeof(packet.header) + sizeof(PACKET_SEND_ENTER_ROOM_RES::UserSize)
		+ sizeof(PACKET_SEND_ENTER_ROOM_RES::RoomIndex)
		+ sizeof(PACKET_SEND_ENTER_ROOM_RES::MyIndex)
		+ sizeof(USER_DATA) * UserSize;
	packet.RoomIndex = index;
	packet.UserSize = UserSize;
	packet.MyIndex = MapUser[sock]->MyIndexRoom;

	int i = 0;
	for (auto iter = MapUser.begin(); iter != MapUser.end(); ++iter, ++i)
	{
		strcpy(packet.data[i].id, iter->second->id);
		packet.data[i].index = iter->second->MyIndexRoom;
		packet.data[i].CharacterIndex = iter->second->CharacterIndex;
	}
	send(sock, (const char *)&packet, packet.header.wLen, 0);
}

void Room::AllSendUserData(SOCKET sock)
{
	PACKET_ROOM_USER packet;
	packet.header.wIndex = PACKET_INDEX_SEND_USER;
	packet.header.wLen = sizeof(packet.header) +
		(sizeof(PACKET_ROOM_USER::MyIndex) + sizeof(char) * SHORT_BUFSIZE);

	packet.data.index = MapUser[sock]->MyIndexRoom;
	packet.data.CharacterIndex = MapUser[sock]->CharacterIndex;
	strcpy(packet.data.id, MapUser[sock]->id);
	packet.MyIndex = MapUser[sock]->MyIndexRoom;

	for (auto iter = MapUser.begin(); iter != MapUser.end(); ++iter)
	{
		if (iter->first != sock)
			send(iter->first, (const char*)&packet, packet.header.wLen, 0);
	}
}