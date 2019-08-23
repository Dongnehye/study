#include "ElevatorManager.h"
#include <iostream>
#include <time.h>
#include <math.h>

ElevatorManager::ElevatorManager()
{
	IsAuto = false;
	mGoalTopFloor = NULL;
	mGoalBottonFloor = NULL;
}


ElevatorManager::~ElevatorManager()
{
	VecElevatorPtr.clear();
	EMListPeoplePtr.clear();
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
		CreatePeople();
	}

	SetGoalFloor();

	ElevatorActive();

	for (auto iter = VecElevatorPtr.begin(); iter != VecElevatorPtr.end(); ++iter)
	{
		(*iter)->Updata();
	}
	//VecElevatorPtr[0]->Updata();

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
				cout << "옥상";
			else if (i == 1)
				cout << "▩";
			else if (j == WITDH - 1)
			{
				cout << "Info : ";
				cout << "People : ";
				cout << CountFloor[HEIGHT - i - 1] << " ";
			}
			else if( j % 3 == 0 && VecElevatorPtr[(j / 3) - 1]->GetFloor() == (HEIGHT - i))
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
	
	cout << "Goal : " << mGoalTopFloor << endl;
	cout << "Goal : " << mGoalBottonFloor << endl;
}

void ElevatorManager::CreatePeople()
{
	//if ((rand() % 100) > PERCENTAGE)
	//{
	//}
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

void ElevatorManager::ElevatorActive()
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
		else if (piter->GetActive() == true && piter->GetIsCommand())
		{
			if(piter->GetArrow() == Aup)
				piter->SetGoalFloor(mGoalTopFloor);
			else if (piter->GetArrow() == Adown)
				piter->SetGoalFloor(mGoalBottonFloor);
			//break;
			
		}
	}
}

int ElevatorManager::nearingFloor(list<AElevator*>::iterator argc_iter)
{
	int fclose_num = 0;
	int sclose_num = 0;
	int floor_num = 0;
	(*argc_iter)->GetFloor();
	for (auto iter = EMListPeoplePtr.begin(); iter != EMListPeoplePtr.end(); ++iter)
	{
		if(fclose_num == 0)
			fclose_num = abs((*iter)->GetFloor() - (*argc_iter)->GetFloor());
		else
		{
			sclose_num = abs((*iter)->GetFloor() - (*argc_iter)->GetFloor());
			if (fclose_num > sclose_num)
				floor_num = (*iter)->GetFloor();
			else
				fclose_num = sclose_num;
		}
	}
	return floor_num;
}