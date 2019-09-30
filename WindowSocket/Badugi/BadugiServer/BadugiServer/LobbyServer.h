#pragma once
#include <Windows.h>
#include <map>
#include <vector>
#include "PACKET_HEADER.h"
#include "CommonHeader.h"
#include "User.h"
#include "Room.h"
#include "GameTable.h"
class LobbyServer
{
	int Index;
	std::map<SOCKET, User*> mapUser;
	std::map<int, GameTable*> mapRoom;

	void RoomInit();


public:
	LobbyServer();
	virtual ~LobbyServer();

	int GetUserSize();

	void AddUser(SOCKET sock, User* user);

	void SendLobbyData(SOCKET sock);
	void SendRoomEnter(SOCKET sock, char * Buf, int len);
	void CheckRoomReady(SOCKET sock, char * Buf, int len);

	void SendCardRefresh(SOCKET sock, User * pUser);
	void SendAllCardRefresh(SOCKET sock, User * pUser);

	void SendBetting(SOCKET sock, char * Buf, int len);
	void SendExchange(SOCKET sock, char * Buf, int len);
	void SendTurnRespond(SOCKET sock, char * Buf, int len);
};