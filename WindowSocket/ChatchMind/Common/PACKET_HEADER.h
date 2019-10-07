#pragma once
#pragma pack(1)
#include <Windows.h>

enum PACKET_INDEX
{
	PACKET_INDEX_SEND_LOGIN = 1,
	PACKET_INDEX_SEND_DRAW_POINT,
	PACKET_INDEX_SEND_LOBBY,

};
struct PACKET_HEADER
{
	WORD wIndex;
	WORD wLen;
};

struct PACKET_LOGIN
{
	PACKET_HEADER header;
	int id;
};

#pragma pack()