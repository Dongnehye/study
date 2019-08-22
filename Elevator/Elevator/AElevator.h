#pragma once
#include <iostream>
#include <list>
#include "People.h"
#include "ElevatorManager.h"

#define MAXFLOOR 20

using namespace std;


class ElevatorManager;
class AElevator
{
	int number;
	int safeWeight;
	int peopleNumber;

	int floorNumber;
	int GoalFloor;
	int arrow;
	bool active;
	bool IsCommand;
	list<People*> EListPeoplePtr;

	ElevatorManager * pElevatorManager;
	void SetIsCommand();
	void OutGoalFloor();

public:
	AElevator();
	~AElevator();
	void Updata();

	void Init(ElevatorManager * _pElevatorManager);
	void AddPeople(People * people);

	void DropPeople(int floorNumber);

	void Move();

	void SetActive(bool _isActive);
	bool GetActive() const;

	int GetFloor() const;
	int GetPeopleCount() const;

	void CheckFloor();

	void SetArrow(int _arrow);
	int GetArrow() const;

	void SetGoalFloor(int _GoalFloor);
	bool GetIsCommand();
};