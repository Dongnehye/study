#pragma once
#include "Room.h"
#include "User.h"
#include "PACKET_HEADER.h"
#include <vector>
#include <map>

using namespace std;

class GameTable :
	public Room
{
public:
	int Index;
	int TotalMoney;

	vector<int> Deck;

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

	void CardChange(int Index, User * mapUser);

	void Batting(int Index, User * mapUser,int Bat);

	void CardCombin(map<SOCKET, User*> &mapUser);

	int WinnerPlayer(map<SOCKET, User*> &mapUser);
};