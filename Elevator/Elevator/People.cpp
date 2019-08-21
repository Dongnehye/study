#include "People.h"


People::People()
{
	srand(time(NULL));

	Init();
}


People::~People()
{
}

bool People::Init()
{
	wantFloor = (rand() % 20 )+ 1;
	weight = (rand() % 100) + 40;
	wait = false;

	return false;
}

int People::GetFloor() const
{
	return wantFloor;
}
