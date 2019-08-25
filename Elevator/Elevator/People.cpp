#include "People.h"
#include <time.h>
#include <iostream>
#include "Commonheader.h"

People::People()
{
	Init();
	SetArrow();
}


People::~People()
{
}

bool People::Init()
{
	Floor = (rand() % 20 )+ 1;
	weight = (rand() % 100) + 40;
	wait = false;

	while (true)
	{
		wantFloor = (rand() % 20) + 1;
		if (wantFloor != Floor)
			break;
	}
	return false;
}

bool People::Init(int _Floor, int _wantFloor)
{
	Floor = _Floor;
	wantFloor = _wantFloor;
	weight = (rand() % 100) + 40;

	return false;
}

bool People::Init(int _Floor, int _wantFloor, int _weight)
{
	Floor = _Floor;
	wantFloor = _wantFloor;
	weight = _weight;

	return false;
}

void People::SetArrow()
{
	if (Floor < wantFloor)
		arrow = Aup;
	else
		arrow = Adown;
}

int People::GetFloor() const
{
	return Floor;
}

int People::GetWantFloor() const
{
	return wantFloor;
}
int People::GetArrow() const
{
	return arrow;
}

int People::GetWeight() const
{
	return weight;
}

void People::SetInit(int _floor, int _wantfloor)
{
	Floor = _floor;
	wantFloor = _wantfloor;
	SetArrow();
}