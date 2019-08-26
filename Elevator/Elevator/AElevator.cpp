#include <algorithm>
#include "AElevator.h"
#include "Commonheader.h"

void AElevator::Arrowtrigger()
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

bool AElevator::SetGoalFloor()
{
	int _GoalFloor = 0;
	int temp = 0;

	if (arrow == Aup)
	{
		_GoalFloor = MINFLOOR - 1;
	}
	if (arrow == Adown)
	{
		_GoalFloor = MAXFLOORSIZE;
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
		}
		else
			return false;
	}
	return true;
}

AElevator::AElevator()
{
	WaitCountdown = WAITCOUNTDOWN;
	safeWeight = SAFEWEIGHT;
	floorNumber = 1;
	GoalFloor = 1;
	arrow = Aup;

	active = false;
	IsCommand = true;

	isCountDown = false;
}

AElevator::~AElevator()
{
	for_each(EListPeoplePtr.begin(), EListPeoplePtr.end(), [](auto iter) {delete iter; });
	EListPeoplePtr.clear();
}

void AElevator::Updata()
{
	if (Countdown())
	{
		// dropPeople;
		DropPeople(floorNumber);

		if (!SetGoalFloor())
		{
			SetActive(false);
			IsCommand = true;
		}
		Arrowtrigger();
		CheckFloor();
		// Move.

		if (active)
			Move();
		SetCountdownZero();
	}
}

void AElevator::Init(ElevatorManager * _pElevatorManager)
{
	pElevatorManager = _pElevatorManager;
}

void AElevator::SetFloor(int _floorNumber)
{
	floorNumber = _floorNumber;
}

void AElevator::AddPeople(People * people)
{
	EListPeoplePtr.push_back(people);
}

bool AElevator::CheckSafeWeight(People * people)
{
	int totalWeight = 0;
	for_each(EListPeoplePtr.begin(), EListPeoplePtr.end(), 
		[&totalWeight](auto iter) { totalWeight += (*iter).GetWeight();});

	if (totalWeight + people->GetWeight() < safeWeight)
		return true;
	else
		return false;
}

void AElevator::DropPeople(int floorNumber)
{
	auto iter = EListPeoplePtr.begin();
	auto iterEnd = EListPeoplePtr.end();
	People * ptr;

	while (iter != iterEnd)
	{
		if (floorNumber == (*iter)->GetWantFloor())
		{
			ptr = *iter;
			iter = EListPeoplePtr.erase(iter);
			delete ptr;
			isCountDown = true;
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
		if (arrow == Aup && floorNumber < MAXFLOORSIZE)
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
				if (CheckSafeWeight(*iter))
				{
					EListPeoplePtr.push_back(*iter);
					iter = pElevatorManager->DropPeople(iter);
					isCountDown = true;
				}
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
				if (CheckSafeWeight(*iter))
				{
					EListPeoplePtr.push_back(*iter);
					iter = pElevatorManager->DropPeople(iter);
					isCountDown = true;
				}
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

void AElevator::SetIsCommand(bool _IsCommand)
{
	IsCommand = _IsCommand;
}

bool AElevator::GetIsCommand()
{
	return IsCommand;
}

bool AElevator::Countdown()
{
	if (WaitCountdown == WAITCOUNTDOWN)
	{
		isCountDown = false;
		return true;
	}
	else
	{
		WaitCountdown += 1;
		return false;
	}
}

void AElevator::SetCountdownZero()
{
	if(isCountDown)
		WaitCountdown = 0;
}

int AElevator::GetFloor() const
{
	return floorNumber;
}

int AElevator::GetPeopleCount() const
{
	return EListPeoplePtr.size();
}