#include "GameTable.h"
#include <algorithm>
#include <random>

#define HANDCARD 4

GameTable::GameTable()
{
	UserSIze = 0;
	CurrentTurn = GAME_TURN_CARD_DIVISION;
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
		PlayingPlayerIndex.insert(make_pair(iter->second->index, false));
	}
	TurnPlayerIndex = (*PlayingPlayerIndex.begin()).first;

	CardSwing(mapUser);

}

int GameTable::NextTurn(int Index, int Turn)
{
	bool IsNextTurn = true;
	for (auto iter = PlayingPlayerIndex.begin(); iter != PlayingPlayerIndex.end(); ++iter)
	{
		IsNextTurn = iter->second & IsNextTurn;
		if (!IsNextTurn)
		{
			CurrentPlayer = iter->first;
			break;
		}
	}
	if (IsNextTurn)
	{
		for (auto iter = PlayingPlayerIndex.begin(); iter != PlayingPlayerIndex.end(); ++iter)
		{
			if (PlayingPlayerIndex.begin() == iter)
				CurrentPlayer = iter->first;
			iter->second = false;
		}

		if (CurrentTurn == GAME_TURN_CARD_DIVISION)
		{
			CurrentTurn = GAME_TURN_BATTING;
		}
		else if (CurrentTurn == GAME_TURN_EXCHANGE)
		{
			CurrentTurn = GAME_TURN_BATTING;
		}
	}

	if (CurrentTurn == GAME_TURN_CARD_DIVISION)
	{
		PlayingPlayerIndex[Index] = true;
	}
	else if (CurrentTurn == GAME_TURN_EXCHANGE)
	{
		PlayingPlayerIndex[Index] = true;
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

int GameTable::GetUserSize()
{
	return UserSIze;
}