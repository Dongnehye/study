#include "AElevator.h"
#include "Commonheader.h"


void AElevator::SetIsCommand()
{
	if (active)
	{
		if (floorNumber < GoalFloor)
		{
			SetArrow(Aup);
		}
		else if (floorNumber > GoalFloor)
		{
			SetArrow(Adown);
		}

	}
}

bool AElevator::OutGoalFloor()
{
	int _GoalFloor = 0;
	int temp = 0;

	if (arrow == Aup)
	{
		_GoalFloor = 0;
	}
	if (arrow == Adown)
	{
		_GoalFloor = 20;
	}

	if (floorNumber == GoalFloor)
	{
		for (auto iter = EListPeoplePtr.begin(); iter != EListPeoplePtr.end(); ++iter)
		{
			temp = (*iter)->GetWantFloor();
			if (arrow == Aup)
			{
				if (_GoalFloor < temp)
					_GoalFloor = temp;
			}
			if (arrow == Adown)
			{
				if (_GoalFloor > temp)
					_GoalFloor = temp;
			}
		}
		if (EListPeoplePtr.size() != 0)
		{
			GoalFloor = _GoalFloor;
			IsCommand = false;
		}
		else
			return false;
	}
	return true;
}

AElevator::AElevator()
{
	number = 0;
	safeWeight = 600;
	peopleNumber = 10;
	floorNumber = 1;

	GoalFloor = 1;
	arrow = Aup;
	active = false;
	IsCommand = true;
}

AElevator::~AElevator()
{
}

void AElevator::Updata()
{
	// dropPeople;
	DropPeople(floorNumber);
	
	if (!OutGoalFloor())
	{
		SetActive(false);
		IsCommand = true;
	}

	SetIsCommand();
	CheckFloor();
	// Move.
	if(active)
		Move();
}

void AElevator::Init(ElevatorManager * _pElevatorManager)
{
	pElevatorManager = _pElevatorManager;
}

void AElevator::AddPeople(People * people)
{
	EListPeoplePtr.push_back(people);
}

void AElevator::DropPeople(int floorNumber)
{
	auto iter = EListPeoplePtr.begin();
	auto iterEnd = EListPeoplePtr.end();

	while (iter != iterEnd)
	{
		if (floorNumber == (*iter)->GetWantFloor())
		{
			iter = EListPeoplePtr.erase(iter);
		}
		if (iter != iterEnd)
			++iter;
		else
			break;
	}
}

void AElevator::Move()
{
	if (floorNumber != GoalFloor)
	{
		if (arrow == Aup && floorNumber < MAXFLOOR)
		{
			++floorNumber;
		}
		else if (arrow == Adown && floorNumber > 1)
		{
			--floorNumber;
		}
	}
}

void AElevator::SetActive(bool _isActive)
{
	active = _isActive;
}

bool AElevator::GetActive() const
{
	return active;
}

void AElevator::CheckFloor()
{
	auto iter = pElevatorManager->EMListPeoplePtr.begin();
	auto iterEnd = pElevatorManager->EMListPeoplePtr.end();

	while (iter != iterEnd)
	{
		if (active)
		{
			if ((*iter)->GetFloor() == floorNumber && (*iter)->GetArrow() == arrow)
			{
				EListPeoplePtr.push_back(*iter);
				iter = pElevatorManager->DropPeople(iter);
			}
			if (iter != iterEnd)
				++iter;
			else
				break;
		}
		else
		{
			if ((*iter)->GetFloor() == floorNumber)
			{
				EListPeoplePtr.push_back(*iter);
				iter = pElevatorManager->DropPeople(iter);
			}
			if (iter != iterEnd)
				++iter;
			else
				break;
		}
	}
}

void AElevator::SetArrow(int _arrow)
{
	arrow = _arrow;
}

int AElevator::GetArrow() const
{
	return arrow;
}

int AElevator::GetGoalFloor() const
{
	return GoalFloor;
}

void AElevator::SetGoalFloor(int _GoalFloor)
{
	GoalFloor = _GoalFloor;
}

bool AElevator::GetIsCommand()
{
	return IsCommand;
}

int AElevator::GetFloor() const
{
	return floorNumber;
}

int AElevator::GetPeopleCount() const
{
	return EListPeoplePtr.size();
}