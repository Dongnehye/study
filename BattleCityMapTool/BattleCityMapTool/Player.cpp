#include "Player.h"
#include "MainTool.h"


Player::Player()
{
	point.x = 6;
	point.y = 6;
}


Player::~Player()
{
}

void Player::PositionMoveX(int x)
{
	point.x += x;
	if (point.x >= MAPSIZE - 1)
		point.x = MAPSIZE - 1;
	else if (point.x < 0)
		point.x = 0;

}

void Player::PositionMoveY(int y)
{
	point.y += y;
	if (point.y >= MAPSIZE - 1)
		point.y = MAPSIZE - 1;
	else if (point.y < 0)
		point.y = 0;
}

POINT Player::GetPosition()
{
	return point;
}
