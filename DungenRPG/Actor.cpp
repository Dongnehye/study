#include "Actor.h"

using namespace std;

Actor::Actor()
{
	x = 0;
	y = 0;
}


Actor::~Actor()
{
}

void Actor::printActor()
{
	cout << " ";
}

void Actor::SetPosition(int _x, int _y)
{
	x = _x;
	y = _y;
}
Actor* Actor::GetInstance()
{
	return this;
}