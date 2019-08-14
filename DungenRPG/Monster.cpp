#include "Monster.h"

using namespace std;

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

void Monster::Move()
{
}

void Monster::printActor()
{
	cout << "¢Ã";
}

