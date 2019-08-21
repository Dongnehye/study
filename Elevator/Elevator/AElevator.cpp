#include "AElevator.h"



AElevator::AElevator()
{
	number = 0;
	safeWeight = 600;
	peopleNumber = 10;
	floorNumber = 1;
}


AElevator::~AElevator()
{
}

void AElevator::Updata()
{
	// dropPeople;
	checkFloor(floorNumber);


}

void AElevator::AddPeople(shared_ptr<People> people)
{
	EListPeoplePtr.push_back(people);
}

void AElevator::checkFloor(int floorNumber)
{
	for (auto iter = EListPeoplePtr.begin(); iter != EListPeoplePtr.end(); ++iter)
	{
		if (floorNumber == (*iter)->GetFloor())
		{

		}
	}
}

void AElevator::DropPeople()
{
}
