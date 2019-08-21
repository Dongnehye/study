#pragma once
#include "Commonheader.h"

using namespace std;

enum Arrow
{
	Aup,
	Adown
};
class AElevator
{
	int number;

	int safeWeight;
	int peopleNumber;

	int floorNumber;

	list<shared_ptr<People>> EListPeoplePtr;

public:
	AElevator();
	~AElevator();
	void Updata();

	void AddPeople(shared_ptr<People> people);

	void checkFloor(int floorNumber);

	void DropPeople();
};