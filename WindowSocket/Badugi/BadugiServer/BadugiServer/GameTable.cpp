#include "GameTable.h"
#include <algorithm>
#include <random>

#define HANDCARD 4

GameTable::GameTable()
{
	UserSIze = 0;
	CurrentTurn = GAME_TURN_CARD_DIVISION;
	TotalMoney = 0;
}
GameTable::~GameTable()
{
}

void GameTable::GameStart(std::map<SOCKET, User*>& mapUser)
{
	for (int i = 0; i < CARDS_END; ++i)
	{
		Deck.push_back(i);
	}
	auto rng = default_random_engine{};
	shuffle(begin(Deck), end(Deck), rng);


	for (auto iter = mapUser.begin(); iter != mapUser.end(); ++iter)
	{
		if(iter->second->RoomIndex == Index)
			PlayingPlayerIndex.insert(make_pair(iter->second->index, false));

	}
	TurnPlayerIndex = (*PlayingPlayerIndex.begin()).first;

	CardSwing(mapUser);

}

int GameTable::CheckNextTurn(int Index)
{
	bool IsNextTurn = true;

	PlayingPlayerIndex[Index] = true;
	
	for (auto iter = PlayingPlayerIndex.begin(); iter != PlayingPlayerIndex.end(); ++iter)
	{
		IsNextTurn = iter->second & IsNextTurn;
		if (IsNextTurn == false)
		{
			CurrentPlayer = iter->first;
			break;
		}
	}
	if (IsNextTurn == true)
	{
		CurrentPlayer = PlayingPlayerIndex.begin()->first;
		for (auto iter = PlayingPlayerIndex.begin(); iter != PlayingPlayerIndex.end(); ++iter)
		{
			iter->second = false;
		}
		
		if (CurrentTurn == GAME_TURN_CARD_DIVISION || CurrentTurn == GAME_TURN_EXCHANGE)
		{
			CurrentTurn = GAME_TURN_BATTING;
		}
		else if (CurrentTurn == GAME_TURN_BATTING)
		{
			CurrentTurn = GAME_TURN_EXCHANGE;
		}
	}
	return CurrentTurn;
}

int GameTable::GetNextPlayerIndex()
{
	return CurrentPlayer;
}

void GameTable::CardSwing(map<SOCKET, User*>& mapUser)
{
	for (auto iter = mapUser.begin(); iter != mapUser.end(); ++iter)
	{
		for (int i = 0; i < HANDCARD; ++i)
		{
			iter->second->card.push_back(Deck.back());
			Deck.pop_back();
		}
	}
}

void GameTable::Batting(int Index, User * mapUser, int Bat)
{
	if (Bat == BATTING_CALL)
	{
		mapUser->Money -= 10;
		TotalMoney += 10;
		mapUser->BatState = BATTING_CALL;
	}
	else if (Bat == BATTING_HALF)
	{
		mapUser->Money -= 20;
		TotalMoney += 20;
		mapUser->BatState = BATTING_HALF;
	}
	else if (Bat == BATTING_CHECK)
	{
		mapUser->BatState = BATTING_CHECK;
	}
	else if (Bat == BATTING_DIE)
	{
		mapUser->BatState = BATTING_DIE;
	}
}

int GameTable::GetUserSize()
{
	return UserSIze;
}