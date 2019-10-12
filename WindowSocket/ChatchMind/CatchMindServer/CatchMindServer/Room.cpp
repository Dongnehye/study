#include "Room.h"
#include <iostream>

#define HALFTIME 45

void Room::GameReady()
{
	GameTurn = GAME_TURN_READY;
	AllUserReady = true;
	NowTime = Time;
	PrevTime = Time;
}

bool Room::CheckAllReady()
{
	if (MapUser.size() >= 3 && AllUserReady)
	{
		NowTime = Time;
		if (NowTime - PrevTime == 3)
		{
			return true;
		}
	}
	else
	{
		AllUserReady = false;
	}
	return false;
}

bool Room::CheckRound()
{
	NowTime = Time;
	if (NowTime - PrevTime == 3)
	{
		return true;
	}
	return false;
}

bool Room::CheckDrawReady()
{
	NowTime = Time;
	if (NowTime - PrevTime == 3)
	{
		return true;
	}
	return false;
}

bool Room::CheckDrawTimeOut()
{
	NowTime = Time;
	if (NowTime - PrevTime == 90)
	{
		return true;
	}
	return false;
}

void Room::SendGameTurn(int Turn)
{
	PACKET_SEND_GAME_TURN packet;
	packet.header.wIndex = PACKET_INDEX_SEND_ROOM_GAME_TURN;
	packet.header.wLen = sizeof(packet);

	switch (Turn)
	{
	case GAME_TURN_START:
	{
		packet.GameTurn = Turn;
		packet.FirstUserIndex = 0;
		packet.SecondUserIndex = 0;
		for (auto iter = MapUser.begin(); iter != MapUser.end(); ++iter)
		{
			send(iter->first, (const char*)&packet, packet.header.wLen, 0);
		}
	}
	break;
	case GAME_TURN_ORDER_USER:
	{
		packet.FirstUserIndex = CurrnetTurnUser;
		packet.SecondUserIndex = CurrnetTurnUser + 1;
		packet.GameTurn = GAME_TURN_ORDER_USER;
		for (auto iter = UserOrder.begin(); iter != UserOrder.end(); ++iter)
		{
			send(iter->second, (const char*)&packet, packet.header.wLen, 0);
		}
	}
	break;
	case GAME_TURN_DRAW:
	{
		packet.FirstUserIndex = CurrnetTurnUser++;
		packet.SecondUserIndex = NULL;

		for (auto iter = UserOrder.begin(); iter != UserOrder.end(); ++iter)
		{
			if (iter->first == packet.FirstUserIndex)
			{
				packet.GameTurn = GAME_TURN_DRAW;
			}
			else
			{
				packet.GameTurn = GAME_TURN_WAIT;
			}
			send(iter->second, (const char*)&packet, packet.header.wLen, 0);
		}
	}
	break;
	case GAME_TURN_RESULT:
	{

	}
	break;
	case GAME_TURN_GAMEOVER:
	{

	}
	break;
	}

}

void Room::SendSyncTime()
{
	PACKET_SEND_TIME_SYNC packet;
	packet.header.wIndex = PACKET_INDEX_SEND_ROOM_TIME_SYNC;
	packet.header.wLen = sizeof(packet);
	packet.Time = NowTime - PrevTime;
	for (auto iter = MapUser.begin(); iter != MapUser.end(); ++iter)
	{
		send(iter->first, (const char*)&packet, packet.header.wLen, 0);
	}
}

void Room::SendCheat(SOCKET sock, PACKET_SEND_CHEAT & packet)
{
	for (auto iter = MapUser.begin(); iter != MapUser.end(); ++iter)
	{
		send(iter->first, (const char*)&packet, packet.header.wLen, 0);
	}
}

Room::Room()
{

}


Room::Room(int _index)
{
	index = _index;
	strcpy(RoomName, "한수");
	strcpy(HostId, "기본");
	IsStart = false;

	AllUserReady = false;

	CurrnetTurnUser = 0;
	GameTurn = GAME_TURN_WAIT;

	TimeSync = false;
	Time = 0;
	PrevTime = 0;
	NowTime = 0;
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
			GameReady();
			return true;
		}
	}

	UserOrder.insert(make_pair(i, sock));
	GameReady();
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

void Room::DisConnectUser(SOCKET sock)
{

	PACKET_SEND_EXIT_ROOM packet;
	packet.header.wIndex = PACKET_INDEX_SEND_EXIT_ROOM;
	packet.header.wLen = sizeof(packet);
	packet.Index = MapUser[sock]->MyIndexRoom;
	send(sock, (const char*)&packet, packet.header.wLen, 0);

	packet.header.wIndex = PACKET_INDEX_SEND_OTHER_EXIT_ROOM;

	for (auto iter = MapUser.begin(); iter != MapUser.end(); ++iter)
	{
		if (iter->first != sock)
			send(iter->first, (const char*)&packet, packet.header.wLen, 0);
	}

	UserOrder.erase(MapUser[sock]->MyIndexRoom);
	MapUser.erase(sock);
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

void Room::IncreaseTime()
{
	Time++;
	if (CheckAllReady() && GameTurn == GAME_TURN_READY)
	{
		GameTurn = GAME_TURN_START;
		SendGameTurn(GAME_TURN_START);
		PrevTime = Time;
	}
	if (CheckRound() && GameTurn == GAME_TURN_START)
	{
		GameTurn = GAME_TURN_ORDER_USER;
		SendGameTurn(GAME_TURN_ORDER_USER);
		PrevTime = Time;
	}
	if (CheckDrawReady() && GameTurn == GAME_TURN_ORDER_USER)
	{
		GameTurn = GAME_TURN_DRAW;
		SendGameTurn(GAME_TURN_DRAW);
		TimeSync = true;
		PrevTime = Time;
	}
	if (CheckDrawTimeOut() && GameTurn == GAME_TURN_DRAW)
	{
		GameTurn = GAME_TURN_RESULT;
		SendGameTurn(GAME_TURN_RESULT);
		PrevTime = Time;
	}
	if (TimeSync || (NowTime - PrevTime == HALFTIME && GameTurn == GAME_TURN_DRAW))
	{
		SendSyncTime();
		TimeSync = false;
	}
}
