#pragma once
class Room
{
	int Index;
	int DeckSize; //MAX 52.
	bool IsLobby;

public:
	Room();
	virtual ~Room();
};

