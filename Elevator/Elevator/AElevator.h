#pragma once
#include <iostream>
#include <list>
#include "People.h"
#include "ElevatorManager.h"

using namespace std;

class ElevatorManager;
class AElevator
{
	int safeWeight;
	int GoalFloor;
	int floorNumber;
	int arrow;
	int WaitCountdown;
	bool active;
	bool isCountDown;
	bool IsCommand;
	list<People*> EListPeoplePtr;

	ElevatorManager * pElevatorManager;
	void Arrowtrigger();
	bool SetGoalFloor();

public:
	AElevator();
	~AElevator();
	void Updata();

	void Init(ElevatorManager * _pElevatorManager);
	void SetFloor(int _floorNumber);
	void AddPeople(People * people);

	bool CheckSafeWeight(People * people);

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
	int GetGoalFloor() const;

	void SetIsCommand(bool _IsCommand);
	bool GetIsCommand();

	bool Countdown();
	void SetCountdownZero();
};