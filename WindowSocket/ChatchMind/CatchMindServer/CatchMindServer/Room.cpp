#include "Room.h"

Room::Room()
{
	strcpy(RoomName,"�Ѽ�");
}


Room::Room(int _index)
{
	index = _index;
}

Room::~Room()
{
}

void Room::AddUser(SOCKET sock, User * pUser)
{
	MapUser.insert(make_pair(sock,pUser));
	pUser->RoomIndex = index;
}
