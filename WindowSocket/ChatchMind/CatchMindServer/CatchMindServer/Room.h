#pragma once
#include "Common.h"
#include "User.h"
#include "PACKET_HEADER.h"
#include <map>
#include <vector>
#include <string>

using namespace std;

class Room
{
public:
	int index;

	char RoomName[SHORT_BUFSIZE];
	char HostId[SHORT_BUFSIZE];

	void SetPalyingUser();
	int PlayingUserSize;

	bool CheckAnswerCheat(char * Buf);
	vector<string> VecAnswerWord;
	bool LoadAnswerWord();
	int AnswerIndex;
	int AnswerUserIndex;
	int RandAnswer();

	int CurrnetTurnUser;
	void NextCurrentUser();
	int GameTurn;

	bool TimeSync;
	int Time;
	int PrevTime;
	int NowTime;
	
	bool AllUserReady;
	bool IsStart;
	map<int, SOCKET> UserOrder;
	map<SOCKET, User*> MapUser;
	vector<DRAWLINE> VecLine;

	void GameReady();
	bool CheckTimeAllReady();
	bool CheckTimeRound();
	bool CheckTimeDrawReady();
	bool CheckDrawTimeOut();
	bool CheckTimeGameOver();

	void SendSyncTime();
	void SendGameTurn(int Turn);
	void SendCheat(SOCKET sock, PACKET_SEND_CHEAT &packet);

	void GameReset();
	Room();
public:
	Room(int index, const char * id);
	virtual ~Room();

	bool AddUser(SOCKET sock, User * pUser);
	bool ExitUser(SOCKET sock, User * pUser);
	void DisConnectUser(SOCKET sock);

	void AddLine(int x0, int y0,int x1, int y1, int Color);
	void EchoLine(SOCKET sock, DRAWLINE Line);
	void ClearLine();

	void SendUserData(SOCKET sock);
	void AllSendUserData(SOCKET sock);

	void IncreaseTime();
};