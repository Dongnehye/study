#include "StudentManager.h"
#include <iostream>
using namespace std;

StudentManager::StudentManager()
{
	ptr.reserve(1024);
}


StudentManager::~StudentManager()
{
}

void StudentManager::LoadFile()
{
	FILE* pFile = fopen("save.txt", "r");
	if (pFile != nullptr)
	{
		int iCount = 0;
		fscanf(pFile, "%d\n", &iCount);
		for (int i = 0; i < iCount; i++)
		{
			shared_ptr<Student> pNew = make_shared<Student>();
			pNew->LoadStudent(pFile);

			if (pNew->track == liberal)
			{
				shared_ptr<Student> pLiberaNew = make_shared < LiberalStudent>();
				pLiberaNew->LoadStudent(pFile);
				pNew = pLiberaNew;
			}
			else if (pNew->track == sciences)
			{
				shared_ptr<Student> pScienceNew = make_shared < ScienceStudent>();
				pScienceNew->LoadStudent(pFile);
				pNew = pScienceNew;
			}
			ptr.push_back(pNew);
		}
		fclose(pFile);
	}
}

void StudentManager::PrintMenu()
{
	cout << "1.�Է�" << endl;
	cout << "2.���" << endl;
	cout << "3.����" << endl;
	cout << "4.����" << endl;
	cout << "5.����" << endl;
}


void StudentManager::InputStudent()
{
	int input = 0;
	cout << "����1 �̰�2" << endl;

	shared_ptr<Student> pNew = nullptr;
	if (input == 1)
	{
		pNew = make_shared<LiberalStudent>();
	}
	else if (input == 2)
	{
		pNew = make_shared<ScienceStudent>();
	}
	pNew->InputLine(ptr.size());
	ptr.push_back(pNew);
}

void StudentManager::OutputStudent()
{
	cout << "��ȣ\t�̸�\t����\t����\t����\t����\t���" << endl;
	//vector<Student*>::iterator
	for (auto iter = ptr.begin();  iter != ptr.end(); ++iter)
	{
		(*iter)->PrintLine();
	}
}

void StudentManager::SaveFile()
{
	FILE* pFile = fopen("save.txt", "w");
	fprintf(pFile, "%d\n", ptr.size());
	for (auto iter = ptr.begin(); iter != ptr.end(); ++iter)
	{
		(*iter)->SaveStudent(pFile);
	}
	fclose(pFile);
}
