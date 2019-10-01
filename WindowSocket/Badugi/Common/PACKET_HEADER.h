#pragma once
#include <Windows.h>
#pragma pack(1)

#define ROOMPLAYERSIZE 3
#define CARDSIZE 4
#define SHORTBUFSIZE 20

enum CARD
{
	CARDS_00_DIAMONDS,
	CARDS_01_DIAMONDS,
	CARDS_02_DIAMONDS,
	CARDS_03_DIAMONDS,
	CARDS_04_DIAMONDS,
	CARDS_05_DIAMONDS,
	CARDS_06_DIAMONDS,
	CARDS_07_DIAMONDS,
	CARDS_08_DIAMONDS,
	CARDS_09_DIAMONDS,
	CARDS_10_DIAMONDS,
	CARDS_11_DIAMONDS,
	CARDS_12_DIAMONDS,
	CARDS_13_HEARTS,
	CARDS_14_HEARTS,
	CARDS_15_HEARTS,
	CARDS_16_HEARTS,
	CARDS_17_HEARTS,
	CARDS_18_HEARTS,
	CARDS_19_HEARTS,
	CARDS_20_HEARTS,
	CARDS_21_HEARTS,
	CARDS_22_HEARTS,
	CARDS_23_HEARTS,
	CARDS_24_HEARTS,
	CARDS_25_HEARTS,
	CARDS_26_CLUBS,
	CARDS_27_CLUBS,
	CARDS_28_CLUBS,
	CARDS_29_CLUBS,
	CARDS_30_CLUBS,
	CARDS_31_CLUBS,
	CARDS_32_CLUBS,
	CARDS_33_CLUBS,
	CARDS_34_CLUBS,
	CARDS_35_CLUBS,
	CARDS_36_CLUBS,
	CARDS_37_CLUBS,
	CARDS_38_CLUBS,
	CARDS_39_SPADES,
	CARDS_40_SPADES,
	CARDS_41_SPADES,
	CARDS_42_SPADES,
	CARDS_43_SPADES,
	CARDS_44_SPADES,
	CARDS_45_SPADES,
	CARDS_46_SPADES,
	CARDS_47_SPADES,
	CARDS_48_SPADES,
	CARDS_49_SPADES,
	CARDS_50_SPADES,
	CARDS_51_SPADES,
	CARDS_END,
};
enum GAME_TURN
{
	GAME_TURN_STAY,
	GAME_TURN_READY,
	GAME_TURN_CARD_DIVISION,
	GAME_TURN_EXCHANGE,
	GAME_TURN_BATTING,
	GAME_TURN_GAMEOVER
};
enum CARDCHANGE
{
	CARDCHANGE_CHANGE,
	CARDCHANGE_PASS
};
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
	PACKET_INDEX_SEND_LOBBY,
	PACKET_INDEX_SEND_LOBBYREFRESH,
	PACKET_INDEX_SEND_ROOMENTER,
	PACKET_INDEX_SEND_ROOMENTER_RES,
	PACKET_INDEX_SEND_GAMESTART,
	PACKET_INDEX_SEND_TURN,
	PACKET_INDEX_SEND_CHAT,
	PACKET_INDEX_SEND_READY,
	PACKET_INDEX_SEND_EXCHANGE,
	PACKET_INDEX_SEND_CARD,
	PACKET_INDEX_SEND_ALLCARD,
	PACKET_INDEX_SEND_TURN_RESPOND,
	PACKET_INDEX_SEND_GAMEOVER,
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
struct USER_ROOM_DATA
{
	int iIndex;
	char Id[10];
	WORD Money;
	bool IsHost;
};
struct USER_CARD_DATA
{
	int iIndex;
	WORD Card[4];
};
struct LOBBY_DATA
{
	int iIndex;
	int UserSize;
	bool IsStart;
};
struct LOBBY_DATA_INFO
{
	int iIndex;
	char Buf[SHORTBUFSIZE];
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
	int Index;
};

struct PACKET_USER_DATA
{
	PACKET_HEADER header;
	WORD wCount;
	USER_DATA data[20];
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
struct PACKET_SEND_ROOMENTER_RES
{
	PACKET_HEADER header;
	WORD RoomIndex;
	USER_ROOM_DATA data[ROOMPLAYERSIZE];
	int UserSize;
	bool isRoomEnter;
};
struct PACKET_SEND_GAMESTART
{
	PACKET_HEADER header;
	int FirstTurnIndex;
};
struct PACKET_SEND_CARD
{
	PACKET_HEADER header;
	USER_CARD_DATA data[ROOMPLAYERSIZE];
};
struct PACKET_ALL_SEND_CARD
{
	PACKET_HEADER header;
	int Index;
	USER_CARD_DATA data[ROOMPLAYERSIZE];
};
struct PACKET_SEND_READY
{
	PACKET_HEADER header;
	bool IsReady;
};
struct PACKET_SEND_TURN
{
	PACKET_HEADER header;
	int Index;
	WORD TURN;
};
struct PACKET_SEND_EXCHANGE
{
	PACKET_HEADER header;
	int Index;
	bool Card[CARDSIZE];
};
struct PACKET_SEND_CHEAT
{
	PACKET_HEADER header;
	int RoomIndex;
	int StrLen;
	char Buf[100];
};

#pragma pack()