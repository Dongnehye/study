#include "ElevatorManager.h"
#include <iostream>
#include <time.h>
#include <math.h>
#include <algorithm>

using namespace std;

ElevatorManager::ElevatorManager()
{
	IsAuto = false;
	mGoalTopFloor = NULL;
	mGoalBottonFloor = NULL;
}


ElevatorManager::~ElevatorManager()
{
	for_each(VecElevatorPtr.begin(), VecElevatorPtr.end(), [](auto iter) {delete iter; });
	for_each(EMListPeoplePtr.begin(), EMListPeoplePtr.end(), [](auto iter) {delete iter; });
	VecElevatorPtr.clear();
	EMListPeoplePtr.clear();
}

void ElevatorManager::Init(int elevatorMaxSize)
{
	CreateElevator(elevatorMaxSize);
}

void ElevatorManager::Updata()
{
	InitCountFloor();

	if (IsAuto)
	{
		CreatePeople();
	}

	SetGoalFloor();

	SetElevatorGoalFloor();

	for (auto iter = VecElevatorPtr.begin(); iter != VecElevatorPtr.end(); ++iter)
	{
		(*iter)->Updata();
	}

	CountAddFloor();
}

void ElevatorManager::CreateElevator(int size)
{
	for (int i = 1; i <= size; ++i)
	{
		AElevator * New = new AElevator();
		New->Init(this);
		if (i > size / 2)
		{
			New->SetFloor(MAXFLOORSIZE);
		}
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
	int witdh = (3 * MAXSIZE) + 3;

	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 1; j <= witdh; ++j)
		{
			if (i == 0 && j == witdh / 2 + 5)
				cout << "Neople" << "\t\t 'z'자동으로 시작, x 수동으로 사람입력, c 종료";
			else if (i == 0)
				cout << " ";
			else if (i == 1 && j == witdh)
				cout << "옥상";
			else if (i == 1)
				cout << "▩";
			else if (j == witdh)
			{
				cout << "Info : ";
				cout << "People : ";
				cout << CountFloor[HEIGHT - i - 1] << " ";
			}
			else if (j % 3 == 0 && VecElevatorPtr[(j / 3) - 1]->GetFloor() == (HEIGHT - i))
			{
				cout << "▣";
			}
			else if (j % 3 == 0)
			{
				cout << "  ";
			}
			else
				cout << "▩";
		}
		cout << endl;
	}
	for (auto iter = VecElevatorPtr.begin(); iter != VecElevatorPtr.end(); ++iter)
	{
		cout << "사람 수 : ";
		cout << (*iter)->GetPeopleCount() << "  ";
		cout << "활성화 : ";
		cout << (*iter)->GetActive() << "  ";
		cout << "방향 위 아래: ";
		cout << (*iter)->GetArrow() << "  ";
		cout << "층 수 : ";
		cout << (*iter)->GetFloor() << "  ";
		cout << "도달해야하는 층 : ";
		cout << (*iter)->GetGoalFloor() << endl;
	}
	
	cout << "MaxGoal : " << mGoalTopFloor << endl;
	cout << "MinGoal : " << mGoalBottonFloor << endl;
}

void ElevatorManager::CreatePeople()
{
	People * peoplePtr = new People();
	EMListPeoplePtr.push_back(peoplePtr);
}

void ElevatorManager::CreateManualPeople()
{
	int tfloor = 0;
	int twantfloor = 0;
	int tpeoples = 0;
	system("cls");
	Draw();
	cout << "층수, 도착할 층수, 인원 을 넣어주세요 : ";
	cin >> tfloor >> twantfloor >> tpeoples;

	for (int i = 0; i < tpeoples; ++i)
	{
		People * peoplePtr = new People();
		peoplePtr->SetInit(tfloor, twantfloor);
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
	int _GoalTopFloor = 0;
	int _GoalBottonFloor = 20;
	int Toptemp = 0;
	int Bottontemp = 0;

	for (auto iter = EMListPeoplePtr.begin(); iter != EMListPeoplePtr.end(); ++iter)
	{
		Toptemp = (*iter)->GetFloor();
		if (_GoalTopFloor < Toptemp)
			_GoalTopFloor = Toptemp;

		Bottontemp = (*iter)->GetFloor();
		if (_GoalBottonFloor > Bottontemp)
			_GoalBottonFloor = Bottontemp;
	}

	mGoalTopFloor = _GoalTopFloor;
	mGoalBottonFloor = _GoalBottonFloor;
}

void ElevatorManager::SetElevatorGoalFloor()
{
	for (auto iter = VecElevatorPtr.begin(); iter != VecElevatorPtr.end(); ++iter)
	{
		auto piter = *iter;
		if (piter->GetActive() == false)
		{
			piter->SetActive(true);

			if(piter->GetFloor() < mGoalTopFloor )
				piter->SetGoalFloor(mGoalTopFloor);

			else if(piter->GetFloor() > mGoalBottonFloor)
				piter->SetGoalFloor(mGoalBottonFloor);

			piter->IsCommand = false;
			break;
		}
		else if (piter->GetActive() == true && piter->IsCommand)
		{
			if(piter->GetArrow() == Aup)
				piter->SetGoalFloor(mGoalTopFloor);
			else if (piter->GetArrow() == Adown)
				piter->SetGoalFloor(mGoalBottonFloor);
			break;			
		}
	}
}