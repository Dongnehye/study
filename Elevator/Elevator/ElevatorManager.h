#pragma once
#include "Commonheader.h"
using namespace std;


class ElevatorManager
{
public:
	vector<shared_ptr<AElevator>> VecElevatorPtr;
	list<shared_ptr<People>> EMListPeoplePtr;

public:
	ElevatorManager();
	~ElevatorManager();

	void Init(int elevatorMaxSize);
	void Updata();
	void Draw();

	void CreateElevator(int size);
	void AddElevator(shared_ptr<AElevator> col);

	// auto, manual
	void CreatePeople();


};