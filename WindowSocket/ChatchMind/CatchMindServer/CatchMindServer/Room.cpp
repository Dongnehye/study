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

void Room::AddUser(SOCKET sock, User * pUser)
{
	MapUser.insert(make_pair(sock,pUser));
	pUser->RoomIndex = index;
}
