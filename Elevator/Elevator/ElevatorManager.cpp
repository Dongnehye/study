#include "ElevatorManager.h"

#define PERCENTAGE 90

ElevatorManager::ElevatorManager()
{
	srand(time(NULL));
}


ElevatorManager::~ElevatorManager()
{
}



void ElevatorManager::Init(int elevatorMaxSize)
{
	CreateElevator(elevatorMaxSize);
}

void ElevatorManager::Updata()
{
	CreatePeople();

	for (auto iter = VecElevatorPtr.begin(); iter != VecElevatorPtr.end(); ++iter)
	{
		(*iter)->Updata();
	}

}

void ElevatorManager::CreateElevator(int size)
{
	for (int i = 0; i < size; ++i)
	{
		AddElevator(make_shared<AElevator>());
	}

}

void ElevatorManager::AddElevator(shared_ptr<AElevator> col)
{
	VecElevatorPtr.push_back(col);
}

void ElevatorManager::Draw()
{


}

void ElevatorManager::CreatePeople()
{
	if ((rand() % 100) > PERCENTAGE)
	{
		shared_ptr<People> peoplePtr = make_shared<People>();
		EMListPeoplePtr.push_back(peoplePtr);
	}
}
