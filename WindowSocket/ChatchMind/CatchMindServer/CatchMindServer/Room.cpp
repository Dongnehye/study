#include "Room.h"

Room::Room()
{

}


Room::Room(int _index)
{
	index = _index;
	strcpy(RoomName, "�Ѽ�");
	strcpy(HostId, "�⺻");
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
