#include "Monster.h"
#include "Scene.h"
#include <math.h>

using namespace std;

void Monster::InitScene(Scene *_Scene)
{
	pScene = _Scene;
}
Monster::Monster()
{
	hp = 100;
	mp = 50;
	atk = 10;
	def = 15;
	level = 15;
}

Monster::~Monster()
{
}

void Monster::SetPlayerPos(int _x, int _y)
{
	playerX = _x;
	playerY = _y;
}

void Monster::Move()
{
	if (playerX - x > 0 && playerY - y > 0)
	{
		
	}

	if (y != 0)
	{
		if (!pScene->isWall(x, y - 1))
			--y;
	}
	else if (y != HEGIHT - 1)
	{
		if (!pScene->isWall(x, y + 1))
			++y;
	}
	else if (x != 0)
	{
		if (!pScene->isWall(x - 1, y))
			--x;
	}
	else if (x != WIDTH - 1)
	{
		if (!pScene->isWall(x + 1, y))
			++x;
	}
}

void Monster::printActor()
{
	cout << "¢Ã";
}

