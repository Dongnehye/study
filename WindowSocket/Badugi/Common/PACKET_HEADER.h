#pragma once
#include <Windows.h>
#pragma pack(1)
enum SCENE_INDEX
{
	SCENE_INDEX_LOGIN,
	SCENE_INDEX_LOBBY,
	SCENE_INDEX_ROOM,
};

enum PACKET_INDEX
{
	PACKET_INDEX_LOGIN_RET = 1,
	PACKET_INDEX_LOGIN_RES,
	PACKET_INDEX_USER_DATA,
	PACKET_INDEX_SEND_POS,
	PACKET_INDEX_SEND_LOBBY,
	PACKET_INDEX_SEND_ROOMENTER,
	PACKET_INDEX_SEND_Chat,
	PACKET_INDEX_SEND_READY,
	PACKET_INDEX_SEND_EXCHANGE,
	PACKET_INDEX_SEND_BETTING,
};

struct PACKET_HEADER
{
	WORD wIndex;
	WORD wLen;
};

struct USER_DATA
{
	int iIndex;
	char Id[10];
	char Pw[10];
	WORD Money;
};
struct LOBBY_DATA
{
	int iIndex;
	int UserSize;
	bool IsStart;
};

struct PACKET_LOGIN_RET
{
	PACKET_HEADER header;
	char Id[10];
	char Pw[10];
};

struct PACKET_LOGIN_RES
{
	PACKET_HEADER header;
	bool IsLogin;
	USER_DATA data;
};

struct PACKET_USER_DATA
{
	PACKET_HEADER header;
	WORD wCount;
	USER_DATA data[20];
};

struct PACKET_SEND_POS
{
	PACKET_HEADER header;
	USER_DATA data;
};
struct PACKET_SEND_LOBBYDATA
{
	PACKET_HEADER header;
	WORD LobbySize;
	LOBBY_DATA data[8];
};
struct PACKET_SEND_ROOMENTER
{
	PACKET_HEADER header;
	WORD RoomIndex;
	USER_DATA data;
};
#pragma pack()