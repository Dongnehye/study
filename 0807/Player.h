#pragma once
#include "Map.h"
#include <conio.h>

class Map;
class Player
{
private:
	int playerX = WIDTH / 2;
	int playerY = HEIGHT / 2;

	Map* pMap;
public:
	void Init(Map* _pMap);
	bool inputOperator();
	void checkTreasure();

	Player();
	~Player();
};

