#pragma once
#include <iostream>
#include <list>
#include "People.h"
#include "ElevatorManager.h"

#define MAXFLOOR 20
#define MINFLOOR 1

using namespace std;


class ElevatorManager;
class AElevator
{
	int number;
	int safeWeight;
	int peopleNumber;
	int GoalFloor;
	int floorNumber;
	int arrow;
	bool active;

	list<People*> EListPeoplePtr;

	ElevatorManager * pElevatorManager;
	void SetIsCommand();
	bool OutGoalFloor();

public:
	AElevator();
	~AElevator();
	void Updata();
	bool IsCommand;
	void Init(ElevatorManager * _pElevatorManager);
	void SetFloor(int _floorNumber);
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

	int GetGoalFloor() const;

	void SetGoalFloor(int _GoalFloor);
	bool GetIsCommand();
};