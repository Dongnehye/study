#include "Player.h"

Map * Player::pMap = NULL;
std::vector<Player> Player::Tail;

void Player::Init(Map * _pMap)
{
	pMap = _pMap;
	pMap->SetPlayer(playerX, playerY);
	Tail.push_back(*this);
	arrow = Right;
}

bool Player::OperateInput()
{
	char ch = 0;

	if (kbhit())
	{
		ch = getch();

		if (ch == 'w' )
		{
			arrow = Up;
		}
		else if (ch == 's')
		{
			arrow = Down;
		}
		else if (ch == 'a')
		{
			arrow = Left;
		}
		else if (ch == 'd')
		{
			arrow = Right;
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool Player::Updata()
{
	if (arrow == Up)
	{
		--playerY;
	}
	else if (arrow == Down)
	{
		++playerY;
	}
	else if (arrow == Left)
	{
		--playerX;
	}
	else if (arrow == Right)
	{
		++playerX;
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

	if (CheckDead())
	{
		return false;
	}
	CheckFood();

	for (auto iter = Tail.begin(); iter != Tail.end(); ++iter)
	{
		pMap->SetPlayer(iter->playerX, iter->playerY);
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
	if (pMap->isTileWall(playerX, playerY))
	{
		return true;
	}

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
