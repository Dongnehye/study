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
	vector<int> PlayingPlayerIndex;

public:
	GameTable();
	virtual ~GameTable();
	int GetUserSize();

	void GameStart(map<SOCKET, User*> &mapUser);

	void CardSwing(map<SOCKET, User*> &mapUser);

	void CardChange(map<SOCKET, User*> &mapUser);

	void CardCombin(map<SOCKET, User*> &mapUser);

	int WinnerPlayer(map<SOCKET, User*> &mapUser);
};