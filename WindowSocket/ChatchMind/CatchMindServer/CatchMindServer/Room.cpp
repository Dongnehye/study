#include "Room.h"

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
	if (MapUser.size() <= 8)
	{
		MapUser.insert(make_pair(sock, pUser));
		pUser->RoomIndex = index;
		return true;
	}
	return false;
}

bool Room::ExitUser(SOCKET sock, User * pUser)
{
	return false;
}

void Room::SendUserData(SOCKET sock)
{
	int UserSize = MapUser.size();

	PACKET_SEND_ENTER_ROOM_RES packet;
	packet.header.wIndex = PACKET_INDEX_SEND_ALLUSER;
	packet.header.wLen = sizeof(packet.header) + sizeof(PACKET_SEND_ENTER_ROOM_RES::UserSize)
		+ sizeof(PACKET_SEND_ENTER_ROOM_RES::RoomIndex)
		+ sizeof(USER_DATA) * UserSize;
	packet.RoomIndex = index;
	packet.UserSize = UserSize;

	int i = 0;
	for (auto iter = MapUser.begin(); iter != MapUser.end(); ++iter, ++i)
	{
		strcpy(packet.data[i].id, iter->second->id);
		packet.data[i].index = iter->second->Index;
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

	packet.data.index = MapUser[sock]->Index;
	packet.data.CharacterIndex = MapUser[sock]->CharacterIndex;
	strcpy(packet.data.id, MapUser[sock]->id);
	packet.MyIndex = MapUser[sock]->Index;

	for (auto iter = MapUser.begin(); iter != MapUser.end(); ++iter)
	{
		if (iter->first != sock)
			send(iter->first, (const char*)&packet, packet.header.wLen, 0);
	}
}