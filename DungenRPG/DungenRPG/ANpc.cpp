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
	// ����.
	GameManager * ga;
	if (ntalk == 0)
	{
		ga->GetInstance()->message->messages.push_back("�ȳ��ϽŰ� �ŵ����� �ϰ� ���͸� ������ ���ÿ�");
		++ntalk;
	}
	else if (ntalk > 0)
	{
		ga->GetInstance()->message->messages.push_back("�� ���ÿ�.");
		++ntalk;
	}
}

void ANpc::printActor()
{
	cout << "��";
}
