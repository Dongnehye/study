#include "GameTable.h"
#include <algorithm>
#include <random>

#define HANDCARD 4

GameTable::GameTable()
{
	UserSIze = 0;
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
		PlayingPlayerIndex.push_back(iter->first);
	}
	CardSwing(mapUser);

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
