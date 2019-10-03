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
	int CurrentPlayerIndex;

	list<int> Deck;

	map<SOCKET,User*> PlayingPlayerIndex;

	int TurnPlayerIndex;
	int CurrentTurn;

	SOCKET CurrentPlayer;

public:
	GameTable();
	virtual ~GameTable();
	int GetUserSize();

	void GameEnter(map<SOCKET, User*> &mapUser);

	void GameStart(map<SOCKET, User*> &mapUser);

	int CheckNextTurn(SOCKET sock);

	SOCKET GetNextPlayerSocket();

	void CardSwing(map<SOCKET, User*> &mapUser);

	void CardChange(int Index, User * mapUser, bool * SelectCard);

	void DisconnectPlayer(SOCKET sock);
	void ExitPlayer(SOCKET sock);

	SOCKET WinnerPlayer();

	void GameOver();
};