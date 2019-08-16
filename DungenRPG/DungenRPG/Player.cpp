#include "Player.h"
#include <conio.h>

using namespace std;

void Player::InitScene(Scene *_Scene)
{
	pScene = _Scene;
	arrows = Adown;
	x = pScene->playerX;
	y = pScene->playerY;
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
	if (!pScene->isWall(x,y))
	{
		pScene->SetPlayerPos(x, y, arrows);
	}
}

bool Player::InputButton()
{
	if (kbhit())
	{
		char ch = getch();
		if (ch == 'w' && y != 0)
		{
			if(!pScene->isWall(x, y - 1))
				--y;
			arrows = Aup;
		}
		else if (ch == 's' && y != HEGIHT - 1)
		{
			if (!pScene->isWall(x, y + 1))
				++y;
			arrows = Adown;
		}
		else if (ch == 'a'&& x != 0)
		{
			if (!pScene->isWall(x - 1, y))
				--x;
			arrows = Aleft;
		}
		else if (ch == 'd' && x != WIDTH - 1)
		{
			if (!pScene->isWall(x + 1, y))
				++x;
			arrows = Aright;
		}
		else if (ch == 'k')
		{
			// 확인.
			sendActor(x, y);
			switch (arrows)
			{
			case Aup:
				sendActor(x, y - 1);
				break;
			case Adown:
				sendActor(x, y + 1);
				break;
			case Aleft:
				sendActor(x - 1, y);
				break;
			case Aright:
				sendActor(x + 1, y);
				break;
			default:
				sendActor(x, y + 1);
				break;
			}
		}
		else if (ch == 'l')
		{
			// 취소. 메뉴.
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

void Player::sendActor(int x, int y)
{
	if(pScene->map[y][x] != nullptr)
		pScene->map[y][x]->reaction();
}

void Player::printActor()
{
	cout << "㈜";
}