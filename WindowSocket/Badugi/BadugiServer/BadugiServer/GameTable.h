#pragma once
#include "Room.h"
#include "User.h"
#include "PACKET_HEADER.h"
#include <vector>
#include <list>
#include <map>

using namespace std;

class GameTable
{
public:
	int UserSIze;
	int Index;
	int TotalMoney;

	list<int> Deck;

	map<SOCKET,User*> PlayingPlayerIndex;

	int TurnPlayerIndex;
	int CurrentTurn;

	SOCKET CurrentPlayer;

public:
	GameTable();
	virtual ~GameTable();
	int GetUserSize();

	void GameStart(map<SOCKET, User*> &mapUser);

	int CheckNextTurn(SOCKET sock);

	SOCKET GetNextPlayerSocket();

	void CardSwing(map<SOCKET, User*> &mapUser);

	bool Batting(int Index, User * mapUser,int Bat);

	void CardChange(int Index, User * mapUser, bool * SelectCard);

	void CardCombin(map<SOCKET, User*> &mapUser);

	int WinnerPlayer(map<SOCKET, User*> &mapUser);
};