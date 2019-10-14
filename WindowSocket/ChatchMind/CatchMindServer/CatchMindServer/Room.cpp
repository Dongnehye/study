#include "Room.h"
#include <iostream>
#include <fstream>
#include <random>

bool Room::LoadAnswerWord()
{
	ifstream in("WordDataBase.txt");

	string Word;
	if (!in.is_open())
	{
		return false;
	}
	else
	{
		while (in)
		{
			in >> Word;
			VecAnswerWord.push_back(Word);
		}
		return true;
	}
	return false;
}

int Room::RandAnswer()
{
	int min = 1;
	random_device rn;
	mt19937_64 rnd(rn());

	uniform_int_distribution<int> range(min, VecAnswerWord.size() - 1);

	return range(rnd);
}

void Room::SetPalyingUser()
{
	PlayingUserSize = MapUser.size();
	if (PlayingUserSize > ROOM_PLAYER_SIZE)
	{
		PlayingUserSize = ROOM_PLAYER_SIZE;
	}
}

bool Room::CheckAnswerCheat(char * Buf)
{
	if (strcmp(VecAnswerWord[AnswerIndex].c_str(), Buf) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Room::NextCurrentUser()
{
	CurrnetTurnUser++;
	if (CurrnetTurnUser < PlayingUserSize)
		GameTurn = GAME_TURN_START;
	else
		GameTurn = GAME_TURN_GAMEOVER;
}

void Room::GameReady()
{
	GameTurn = GAME_TURN_READY;
	AllUserReady = true;
	NowTime = Time;
	PrevTime = Time;
}

bool Room::CheckTimeAllReady()
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

bool Room::CheckTimeRound()
{
	NowTime = Time;
	if (NowTime - PrevTime == 3)
	{
		return true;
	}
	return false;
}

bool Room::CheckTimeDrawReady()
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
	if (NowTime - PrevTime == DRAW_TIMEOUT)
	{
		return true;
	}
	return false;
}

bool Room::CheckTimeGameOver()
{
	NowTime = Time;
	if (NowTime - PrevTime == 5)
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
		SetPalyingUser();
		GameTurn = GAME_TURN_START;
		IsStart = true;
		packet.GameTurn = Turn;
		packet.FirstIndex = 0;
		packet.SecondIndex = PlayingUserSize;
		for (auto iter = MapUser.begin(); iter != MapUser.end(); ++iter)
		{
			send(iter->first, (const char*)&packet, packet.header.wLen, 0);
		}
	}
	break;
	case GAME_TURN_ORDER_USER:
	{
		GameTurn = GAME_TURN_ORDER_USER;
		packet.FirstIndex = CurrnetTurnUser;
		packet.SecondIndex = CurrnetTurnUser + 1;
		packet.GameTurn = GAME_TURN_ORDER_USER;
		for (auto iter = UserOrder.begin(); iter != UserOrder.end(); ++iter)
		{
			send(iter->second, (const char*)&packet, packet.header.wLen, 0);
		}
		ClearLine();
	}
	break;
	case GAME_TURN_DRAW:
	{
		GameTurn = GAME_TURN_DRAW;
		packet.FirstIndex = CurrnetTurnUser;
		AnswerIndex = RandAnswer();
		packet.SecondIndex = AnswerIndex;
		for (auto iter = UserOrder.begin(); iter != UserOrder.end(); ++iter)
		{
			if (iter->first == packet.FirstIndex)
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
		GameTurn = GAME_TURN_RESULT;
		PrevTime = Time;
		for (auto iter = UserOrder.begin(); iter != UserOrder.end(); ++iter)
		{
			packet.FirstIndex = CurrnetTurnUser;
			packet.SecondIndex = AnswerUserIndex;
			packet.GameTurn = GAME_TURN_RESULT;	
			send(iter->second, (const char*)&packet, packet.header.wLen, 0);
		}
		AnswerUserIndex = PLAYING_USER_END;
		NextCurrentUser();
	}
	break;
	case GAME_TURN_GAMEOVER:
	{
		PrevTime = Time;
		for (auto iter = UserOrder.begin(); iter != UserOrder.end(); ++iter)
		{
			packet.FirstIndex = NULL;
			packet.SecondIndex = NULL;
			packet.GameTurn = GAME_TURN_GAMEOVER;
			send(iter->second, (const char*)&packet, packet.header.wLen, 0);
		}
		GameReset();
	}
	break;
	}
	PrevTime = Time;
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
	packet.Buf[packet.StrLen] = '\0';

	if (CheckAnswerCheat(packet.Buf))
	{
		AnswerUserIndex = MapUser[sock]->MyIndexRoom;
		MapUser[sock]->Score += 1;
		SendGameTurn(GAME_TURN_RESULT);
	}
	for (auto iter = MapUser.begin(); iter != MapUser.end(); ++iter)
	{
		send(iter->first, (const char*)&packet, packet.header.wLen, 0);
	}
}

void Room::GameReset()
{
	IsStart = false;
	AnswerIndex = NULL;
	AnswerUserIndex = PLAYING_USER_END;
	PlayingUserSize = NULL;
	CurrnetTurnUser = 0;
	GameTurn = GAME_TURN_READY;
	TimeSync = false;
	Time = NULL;
	PrevTime = NULL;
	NowTime = NULL;

	for (auto iter = MapUser.begin(); iter != MapUser.end(); ++iter)
	{
		iter->second->Score = NULL;
	}
}

Room::Room()
{

}


Room::Room(int _index, const char * id)
{
	index = _index;
	strcpy(RoomName, id);
	strcpy(HostId, "기본");

	if (!LoadAnswerWord())
		cout << index << " : 방 단어 로드 에러()" << endl;

	AnswerIndex = NULL;
	AnswerUserIndex = PLAYING_USER_END;

	IsStart = false;

	AllUserReady = false;

	PlayingUserSize = NULL;
	CurrnetTurnUser = 0;
	GameTurn = GAME_TURN_WAIT;

	TimeSync = false;
	Time = NULL;
	PrevTime = NULL;
	NowTime = NULL;
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

void Room::ClearLine()
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
	if (CheckTimeAllReady() && GameTurn == GAME_TURN_READY)
	{
		SendGameTurn(GAME_TURN_START);
	}
	if (CheckTimeRound() && GameTurn == GAME_TURN_START)
	{
		SendGameTurn(GAME_TURN_ORDER_USER);
	}
	if (CheckTimeDrawReady() && GameTurn == GAME_TURN_ORDER_USER)
	{
		SendGameTurn(GAME_TURN_DRAW);
		TimeSync = true;
	}
	if ((CheckDrawTimeOut() && GameTurn == GAME_TURN_DRAW))
	{
		SendGameTurn(GAME_TURN_RESULT);
	}	
	if ((CheckTimeGameOver() && GameTurn == GAME_TURN_GAMEOVER))
	{
		SendGameTurn(GAME_TURN_GAMEOVER);
	}
	if (TimeSync || (NowTime - PrevTime == HALFTIME && GameTurn == GAME_TURN_DRAW))
	{
		SendSyncTime();
		TimeSync = false;
	}

}
