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

	map<int,bool> PlayingPlayerIndex;

	int TurnPlayerIndex;
	int CurrentTurn;

	int CurrentPlayer;

public:
	GameTable();
	virtual ~GameTable();
	int GetUserSize();

	void GameStart(map<SOCKET, User*> &mapUser);

	int CheckNextTurn(int Index);

	int GetNextPlayerIndex();

	void CardSwing(map<SOCKET, User*> &mapUser);

	void Batting(int Index, User * mapUser,int Bat);

	void CardChange(int Index, User * mapUser, bool * SelectCard);

	void CardCombin(map<SOCKET, User*> &mapUser);

	int WinnerPlayer(map<SOCKET, User*> &mapUser);
};