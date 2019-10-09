#pragma once
#include "Common.h"
#include "PACKET_HEADER.h"
#include "User.h"
#include "Room.h"
#include <map>
#include <vector>

class LobbyServer
{
	int gRoomIndex;

	std::map<SOCKET, User*> MapUser;
	std::map<int, Room*> MapRoom;

	void RoomInit();
	void CreateRoom(SOCKET sock);

public:
	LobbyServer();
	virtual ~LobbyServer();

	int GetUserSize();

	void AddUser(SOCKET sock, User* user);

	void SendCheat(SOCKET sock, char * Buf, int len);
	void SendLobbyData(SOCKET sock);
	void SendUserData(SOCKET sock);
	void SendRoomUserData(SOCKET sock);
	void AllSendUserData(SOCKET sock);

	void SendRoomEnter(SOCKET sock, char * Buf, int len);
	void CheckRoomReady(SOCKET sock, char * Buf, int len);

	void DisconnectPlayer(SOCKET sock);
	void ExitPlayer(SOCKET sock);

	void ProcessPacket(SOCKET sock, User * pUser,DWORD PacketIndex);
};