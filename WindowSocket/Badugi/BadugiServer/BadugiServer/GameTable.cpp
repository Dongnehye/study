#include "GameTable.h"
#include <algorithm>
#include <random>

#define HANDCARD 4
#define EQUALCARD 13

GameTable::GameTable()
{
	UserSIze = 0;
	CurrentTurn = GAME_TURN_CARD_DIVISION;
	TotalMoney = 0;
}
GameTable::~GameTable()
{
}
template < typename T > 
void shuffle(std::list<T>& lst)
{

	vector< std::reference_wrapper< const T > > vec(lst.begin(), lst.end());

	shuffle(vec.begin(), vec.end(), std::mt19937{ std::random_device{}() });

	list<T> shuffled_list{ vec.begin(), vec.end() };

	lst.swap(shuffled_list);
}

void GameTable::GameStart(std::map<SOCKET, User*>& mapUser)
{
	CurrentTurn = GAME_TURN_CARD_DIVISION;
	for (int i = 0; i < CARDS_END; ++i)
	{
		Deck.push_back(i);
	}
	auto rng = default_random_engine{};
	shuffle(Deck);
	
	for (auto iter = mapUser.begin(); iter != mapUser.end(); ++iter)
	{
		if(iter->second->RoomIndex == Index)
			PlayingPlayerIndex.insert(make_pair(iter->first, iter->second));
	}
	TurnPlayerIndex = (*PlayingPlayerIndex.begin()).second->index;

	CardSwing(mapUser);

}

int GameTable::CheckNextTurn(SOCKET sock)
{
	bool IsNextTurn = true;

	SOCKET Winner = WinnerPlayer();
	if (Winner != NULL)
	{
		CurrentPlayer = Winner;
		return GAME_TURN_GAMEOVER;
	}

	PlayingPlayerIndex[sock]->IsTurnActiveEnd = true;

	for (auto iter = PlayingPlayerIndex.begin(); iter != PlayingPlayerIndex.end(); ++iter)
	{
		IsNextTurn = iter->second->IsTurnActiveEnd & IsNextTurn;
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
			iter->second->IsTurnActiveEnd = false;
		}

		if (CurrentTurn == GAME_TURN_CARD_DIVISION )
		{
			CurrentTurn = GAME_TURN_EXCHANGE;
		}
	}
	return CurrentTurn;
}

SOCKET GameTable::GetNextPlayerSocket()
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

void GameTable::CardChange(int Index, User * mapUser, bool * SelectCard)
{
	for (int i = 0; i < CARDSIZE; ++i)
	{
		if (SelectCard[i])
		{
			Deck.push_front(mapUser->card[i]);
			mapUser->card[i] = Deck.back();
			Deck.pop_back();
		}
	}
}

SOCKET GameTable::WinnerPlayer()
{
	bool IsWin;

	for (auto iter = PlayingPlayerIndex.begin(); iter != PlayingPlayerIndex.end(); ++iter)
	{
		sort(iter->second->card.begin(), iter->second->card.end());
	}

	for (auto iter = PlayingPlayerIndex.begin(); iter != PlayingPlayerIndex.end(); ++iter)
	{
		IsWin = true;
		vector<int>::iterator prevCard = iter->second->card.begin();
		for (auto carditer = iter->second->card.begin(); carditer != iter->second->card.end(); ++carditer)
		{
			if (carditer != iter->second->card.begin() || ++carditer != iter->second->card.end())
			{
				if ((*prevCard) + EQUALCARD != (*carditer))
				{
					IsWin = false;
				}
				else
				{
					prevCard = carditer;
				}
			}
		}
		if (IsWin)
			return iter->first;
	}
	return NULL;
}

int GameTable::GetUserSize()
{
	return UserSIze;
}