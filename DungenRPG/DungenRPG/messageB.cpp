#include "messageB.h"

messageB::messageB()
{
	messages.push_back("테스트1");
	messages.push_back("테스트2");
	messages.push_back("테스트3");
	messages.push_back("테스트4");
	messages.push_back("테스트5");
	messages.push_back("테스트6");
	messages.push_back("테스트7");
}


messageB::~messageB()
{
}

void messageB::Draw()
{
	int count = 0;
	for (auto riter(messages.rbegin()); riter != messages.rend(); ++riter)
	{
		if (count < 4)
		{
			cout << *riter << endl;
			++count;
		}
		else if (count > 10)
		{
			// 제거.
		}
	}
}
