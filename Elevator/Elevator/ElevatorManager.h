#pragma once
#include <vector>
#include <list>
#include <memory>
#include "People.h"
#include "AElevator.h"
#include "Commonheader.h"


class People;
class AElevator;
class ElevatorManager
{
private:
	bool IsAuto;
	int CountFloor[MAXFLOORSIZE];

public:
	std::vector<AElevator*> VecElevatorPtr;
	std::list<People*> EMListPeoplePtr;

public:
	ElevatorManager();
	~ElevatorManager();

	int mGoalTopFloor;
	int mGoalBottonFloor;

	void Init(int elevatorMaxSize);
	void Updata();
	void Draw();

	void CreateElevator(int size);
	void AddElevator(AElevator * col);
	
	void InitCountFloor();
	void CountAddFloor();

	// auto, manual
	void CreatePeople();
	void CreateManualPeople();
	std::list<People*>::iterator DropPeople(std::list<People*>::iterator iter);

	void SetIsAuto(bool _IsAuto);

	void SetGoalFloor();
	void SetElevatorGoalFloor();
};