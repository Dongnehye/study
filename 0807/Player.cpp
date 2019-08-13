#include "Player.h"
#include <iostream>


Player::Player()
{

}

Player::~Player()
{

}
void Player::Init(Map* _pMap)
{
	pMap = _pMap;
	pMap->SetPlayer(playerX, playerY);
}
bool Player::inputOperator()
{
	char ch = getch();
	pMap->SetEmpty(playerX, playerY);
	if (ch == 'w' && !pMap->isTileWall(playerX, playerY - 1))
		--playerY;
	else if (ch == 's'&& !pMap->isTileWall(playerX, playerY + 1))
		++playerY;
	else if (ch == 'a'&& !pMap->isTileWall(playerX - 1, playerY))
		--playerX;
	else if (ch == 'd'&& !pMap->isTileWall(playerX + 1, playerY))
		++playerX;

	pMap->SetPlayer(playerX, playerY);

	return false;
}

void Player::checkTreasure()
{
	//if (map[y][x] == TREASURE)
	//{
	//	map[y][x] = EMPTY;
	//	score += 100;
	//}
}
