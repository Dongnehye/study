#pragma once
#include "Map.h"
#include <conio.h>
#include <vector>

class Map;
class Player
{
private:
	int playerX = WIDTH / 2;
	int playerY = HEIGHT / 2;
	static Map* pMap;
	static std::vector<Player> Tail;

public:
	void Init(Map* _pMap);
	bool OperateInput();
	void CheckFood();
	bool CheckDead();

public:
	Player();
	Player(int x, int y);
	~Player();

	inline void SetPlayerPos(int x, int y)
	{
		playerX = x;
		playerY = y;
	}

};

