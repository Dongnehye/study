#include "ANpc.h"

ANpc::ANpc()
{
	ntalk = 0;
}


ANpc::~ANpc()
{
}

void ANpc::reaction()
{
	// 응답.
	GameManager * ga;
	if (ntalk == 0)
	{
		ga->GetInstance()->message->messages.push_back("안녕하신가 거두절미 하고 몬스터를 잡으러 가시오");
		++ntalk;
	}
	else if (ntalk > 0)
	{
		ga->GetInstance()->message->messages.push_back("잘 가시오.");
		++ntalk;
	}
}

void ANpc::printActor()
{
	cout << "ⓝ";
}
