#pragma once
#include <Windows.h>
#pragma pack(1)
enum SCENE_INDEX
{
	SCENE_INDEX_LOGIN = 1,
	SCENE_INDEX_LOBBY,
	SCENE_INDEX_ROOM,
};

enum PACKET_INDEX
{
	PACKET_INDEX_LOGIN_RET = 1,
	PACKET_INDEX_LOGIN_RES,
	PACKET_INDEX_USER_DATA,
	PACKET_INDEX_SEND_POS,
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
	WORD Id;
	WORD Pw;
	WORD Money;
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
	int iIndex;
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


#pragma pack()