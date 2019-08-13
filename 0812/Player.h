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
	bool Updata();
	void CheckFood();
	bool CheckDead();

	enum Arrows
	{
		Up,
		Down,
		Left,
		Right
	};
	int arrow;

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

