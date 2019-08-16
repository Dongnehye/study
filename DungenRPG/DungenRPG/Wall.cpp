#include "Wall.h"

using namespace std;

Wall::Wall()
{
}

void Wall::Init(bool _binvisual)
{
	binvisual = _binvisual;
}


Wall::~Wall()
{
}

void Wall::printActor()
{
	if (!binvisual)
		cout << "бс";
	else
		cout << "  ";
}