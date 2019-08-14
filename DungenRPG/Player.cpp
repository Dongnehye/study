#include "Player.h"
#include <conio.h>

using namespace std;

void Player::Init(Scene *_Scene)
{
	pScene = _Scene;
	pScene->SetPlayerPos(x, y);
}

Player::Player()
{
	playerName.reserve(256);
	playerName = "KSJ";
	hp = 100;
	mp = 50;
	atk = 10;
	def = 15;
	level = 15;
	exp = 15;
}


Player::~Player()
{
	//vector 해제 넣어야함.
	item.clear();
}

void Player::Move()
{
	pScene->SetPlayerPos(x, y);
}

bool Player::InputButton()
{
	if (kbhit())
	{
		char ch = getch();
		if (ch == 'w' && y != 0)
		{
			--y;
		}
		else if (ch == 's' && y != HEGIHT - 1)
		{
			++y;
		}
		else if (ch == 'a'&& x != 0)
		{
			--x;
		}
		else if (ch == 'd' && x != WIDTH - 1)
		{
			++x;
		}
		else if (ch == 'k')
		{

		}
		else if (ch == 'l')
		{

		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	return true;
}

void Player::printActor()
{
	cout << "㈜";
}
