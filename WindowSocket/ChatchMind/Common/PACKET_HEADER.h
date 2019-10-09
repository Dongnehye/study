#pragma once
#pragma pack(1)
#include <Windows.h>

#define SHORT_BUFSIZE 20
#define LONG_BUFSIZE 200
#define ROOMPLAYERSIZE 8

enum SCENE_INDEX
{
	SCENE_INDEX_LOGIN,
	SCENE_INDEX_LOBBY,
	SCENE_INDEX_ROOM,
	SCENE_INDEX_END,
};
enum PACKET_INDEX
{
	PACKET_INDEX_SEND_LOGIN = 1,
	PACKET_INDEX_SEND_DRAW_POINT,
	PACKET_INDEX_SEND_LOBBY,
	PACKET_INDEX_SEND_ALLUSER,
	PACKET_INDEX_SEND_USER,
	PACKET_INDEX_SEND_CHEAT,
	PACKET_INDEX_SEND_ENTER_ROOM,
	PACKET_INDEX_SEND_EXIT_ROOM,
	PACKET_INDEX_SEND_ROOM_ALLUSER,
	PACKET_INDEX_SEND_ROOM_USER,
};
enum CHARACTER_INDEX
{
	CHARACTER_INDEX = 1,
};
struct PACKET_HEADER
{
	WORD wIndex;
	WORD wLen;
};
struct USER_DATA
{
	int index;
	int CharacterIndex;
	char id[SHORT_BUFSIZE];
};
struct LOBBY_DATA
{
	int RoomIndex;
	int UserSize;
	bool IsStart;
	char Title[SHORT_BUFSIZE];
	char Hostid[SHORT_BUFSIZE];
};

struct PACKET_LOGIN
{
	PACKET_HEADER header;
	char id[SHORT_BUFSIZE];
	char pw[SHORT_BUFSIZE];
};
struct PACKET_LOGIN_RES
{
	PACKET_HEADER header;
	int Myindex;
	bool IsLogin;
};
struct PACKET_LOBBY_ENTER
{
	PACKET_HEADER header;
};
struct PACKET_USER_REQUEST
{
	PACKET_HEADER header;
};
struct PACKET_LOBBY_REFRESH
{
	PACKET_HEADER header;
	int LobbySize;
	LOBBY_DATA data[SHORT_BUFSIZE];
};
struct PACKET_ROOM_ALLUSER
{
	PACKET_HEADER header;
	int MyIndex;
	int UserSize;
	USER_DATA data[SHORT_BUFSIZE];
};
struct PACKET_ROOM_USER
{
	PACKET_HEADER header;
	int MyIndex;
	USER_DATA data;
};
struct PACKET_SEND_CHEAT
{
	PACKET_HEADER header;
	int RoomIndex;
	int StrLen;
	char Buf[LONG_BUFSIZE];
};
struct PACKET_SEND_ENTER_ROOM
{
	PACKET_HEADER header;
	WORD RoomIndex;
};
struct PACKET_SEND_ENTER_ROOM_RES
{
	PACKET_HEADER header;
	WORD RoomIndex;
	int UserSize;
	USER_DATA data[ROOMPLAYERSIZE];
};
struct PACKET_SEND_EXIT_ROOM
{
	PACKET_HEADER header;
	int Index;
};

#pragma pack()