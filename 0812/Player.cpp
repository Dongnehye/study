#include "Player.h"

Map * Player::pMap = NULL;
std::vector<Player> Player::Tail;

void Player::Init(Map * _pMap)
{
	pMap = _pMap;
	pMap->SetPlayer(playerX, playerY);
	Tail.push_back(*this);
}

bool Player::OperateInput()
{
	char ch = 0;

	if (kbhit())
	{
		ch = getch();

		if (ch == 'w' && !pMap->isTileWall(playerX, playerY - 1))
		{
			--playerY;
		}
		else if (ch == 's' && !pMap->isTileWall(playerX, playerY + 1))
		{
			++playerY;
		}
		else if (ch == 'a' && !pMap->isTileWall(playerX - 1, playerY))
		{
			--playerX;
		}
		else if (ch == 'd' && !pMap->isTileWall(playerX + 1, playerY))
		{
			++playerX;
		}
		else
		{
			return false;
		}

		for (auto iter = Tail.begin(); iter != Tail.end(); ++iter)
		{
			pMap->SetEMPTYPlayer(iter->playerX, iter->playerY);
		}

		for (auto iter = Tail.end() - 1; iter != Tail.begin(); --iter)
		{
			if (iter != Tail.begin())
			{
				auto temp = iter;
				--temp;
				iter->SetPlayerPos(temp->playerX, temp->playerY);
			}
		}

		Tail.front().SetPlayerPos(playerX, playerY);

		CheckFood();

		for (auto iter = Tail.begin(); iter != Tail.end(); ++iter)
		{
			pMap->SetPlayer(iter->playerX, iter->playerY);
		}
	}
	return true;
}

void Player::CheckFood()
{
	if (pMap->CheckFood(playerX, playerY))
	{
		Player player(0, 0);
		Tail.push_back(player);
	}
}
bool Player::CheckDead()
{
	for (auto iter = Tail.begin() + 1; iter != Tail.end(); ++iter)
	{
		if (Tail.begin()->playerX == iter->playerX && Tail.begin()->playerY == iter->playerY)
			return true;
	}
	return false;
}
Player::Player()
{

}
Player::Player(int x, int y)
{
	playerX = x;
	playerY = y;
}
Player::~Player()
{

}
