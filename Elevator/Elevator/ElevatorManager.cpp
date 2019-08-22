#include "ElevatorManager.h"
#include <iostream>
#include <time.h>

#define PERCENTAGE 60
#define HEIGHT 22
#define WITDH 16

ElevatorManager::ElevatorManager()
{
	srand(time(NULL));
	IsAuto = true;
	mGoalFloor = NULL;
}


ElevatorManager::~ElevatorManager()
{
}

void ElevatorManager::Init(int elevatorMaxSize)
{
	CreateElevator(elevatorMaxSize);
	//VecElevatorPtr[0]->SetActive(true);
}

void ElevatorManager::Updata()
{
	InitCountFloor();

	if (IsAuto)
	{

	}
	// Manual
	else
	{
		
	}

	CreatePeople();

	SetGoalFloor();

	ElevatorActive();

	for (auto iter = VecElevatorPtr.begin(); iter != VecElevatorPtr.end(); ++iter)
	{
		(*iter)->Updata();
	}


	CountAddFloor();
}

void ElevatorManager::CreateElevator(int size)
{
	for (int i = 0; i < size; ++i)
	{
		AElevator * New = new AElevator();
		New->Init(this);
		AddElevator(New);
	}

}

void ElevatorManager::AddElevator(AElevator * col)
{
	//col->Init(this);
	VecElevatorPtr.push_back(col);
}

void ElevatorManager::CountAddFloor()
{
	auto iter = EMListPeoplePtr.begin();

	for (; iter != EMListPeoplePtr.end(); ++iter)
	{
		CountFloor[(*iter)->GetFloor() - 1] += 1;
	}

}

void ElevatorManager::InitCountFloor()
{
	memset(CountFloor,NULL,sizeof(CountFloor));
}

void ElevatorManager::Draw()
{
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 1; j < WITDH; ++j)
		{
			if (i == 0 && j == WITDH / 2 + 5)
				cout << "Neople";
			else if(i == 0)
				cout << " ";
			else if (i == 1 && j == WITDH - 1)
				cout << "¿Á»ó";
			else if (i == 1)
				cout << "¢Ì";
			else if (j == WITDH - 1)
			{
				cout << "Info : ";
				cout << "People : ";
				cout << CountFloor[HEIGHT - i - 1];
			}
			else if( j % 3 == 0 && VecElevatorPtr[(j / 3) - 1]->GetFloor() == (HEIGHT - i))
			{
				cout << "¢Ã";
			}
			else if (j % 3 == 0)
			{
				cout << "  ";
			}
			else
				cout << "¢Ì";
		}
		cout << endl;
	}
	for (auto iter = VecElevatorPtr.begin(); iter != VecElevatorPtr.end(); ++iter)
	{
		cout << (*iter)->GetPeopleCount() << endl;
	}
}

void ElevatorManager::CreatePeople()
{
	if ((rand() % 100) > PERCENTAGE)
	{
		People * peoplePtr = new People();
		EMListPeoplePtr.push_back(peoplePtr);
	}
}

list<People*>::iterator ElevatorManager::DropPeople(list<People*>::iterator iter)
{
	return EMListPeoplePtr.erase(iter);
}

void ElevatorManager::SetIsAuto(bool _IsAuto)
{
	IsAuto = _IsAuto;
}

void ElevatorManager::SetGoalFloor()
{
	int _GoalFloor = 0;
	int temp = 0;
	for (auto iter = EMListPeoplePtr.begin(); iter != EMListPeoplePtr.end(); ++iter)
	{
		temp = (*iter)->GetFloor();
		if (_GoalFloor < temp)
			_GoalFloor = temp;

	}
	mGoalFloor = _GoalFloor;
}

void ElevatorManager::ElevatorActive()
{
	for (auto iter = VecElevatorPtr.begin(); iter != VecElevatorPtr.end(); ++iter)
	{
		if ((*iter)->GetActive() == true)
		{
			if ((*iter)->GetIsCommand())
			{
				(*iter)->SetGoalFloor(mGoalFloor);
				break;
			}
		}
		else if ((*iter)->GetActive() == false)
		{
			(*iter)->SetActive(true);
			(*iter)->SetGoalFloor(mGoalFloor);
			//(*iter)->(true);
			break;
		}

	}
}