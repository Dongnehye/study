#pragma once
#include "Room.h"
#include <vector>

using namespace std;



class GameTable :
	public Room
{
public:
	int DeckSize; //MAX 52.
	vector<int> Deck;

public:
	GameTable();
	virtual ~GameTable();
};

