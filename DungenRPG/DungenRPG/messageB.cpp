#include "messageB.h"

messageB::messageB()
{
	messages.push_back("�׽�Ʈ1");
	messages.push_back("�׽�Ʈ2");
	messages.push_back("�׽�Ʈ3");
	messages.push_back("�׽�Ʈ4");
	messages.push_back("�׽�Ʈ5");
	messages.push_back("�׽�Ʈ6");
	messages.push_back("�׽�Ʈ7");
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
			// ����.
		}
	}
}
