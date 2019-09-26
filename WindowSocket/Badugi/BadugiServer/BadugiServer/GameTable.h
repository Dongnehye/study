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
	int Index;
public:
	int DeckSize; //MAX 52.
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

	int NextTurn(int Index, int Turn);

	int GetNextPlayerIndex();

	void CardSwing(map<SOCKET, User*> &mapUser);

	void CardChange(map<SOCKET, User*> &mapUser);

	void CardCombin(map<SOCKET, User*> &mapUser);

	int WinnerPlayer(map<SOCKET, User*> &mapUser);
};