#include "StudentManager.h"
#include <iostream>
using namespace std;

StudentManager::StudentManager()
{
	st.reserve(1024);
}


StudentManager::~StudentManager()
{
	for (auto iter = st.begin(); iter != st.end(); ++iter)
	{
		delete *iter;
	}

	st.clear();
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
			Student * pNew = new Student();
			pNew->LoadStudent(pFile);
			if (pNew->track == liberal)
			{
				Student * pLiberaNew = new LiberalStudent();
				pLiberaNew = dynamic_cast<LiberalStudent*>(pNew);
				pLiberaNew->LoadStudent(pFile);
			}
			//else (pNew->track == sciences)
			//{

			//}
			st.push_back(pNew);
		}
		fclose(pFile);
	}
}

void StudentManager::PrintMenu()
{
	cout << "1.입력" << endl;
	cout << "2.출력" << endl;
	cout << "3.저장" << endl;
	cout << "4.종료" << endl;
}


void StudentManager::InputStudent()
{
	int input = 0;
	cout << "문과1 이과2" << endl;

	Student * pNew = nullptr;
	if (input == 1)
	{
		Student * pNew = new LiberalStudent();
	}
	else if (input == 2)
	{
		//Student * pNew = new ScienceStudent();
	}
	pNew->InputLine(st.size());
	st.push_back(pNew);
}

void StudentManager::OutputStudent()
{
	cout << "번호\t이름\t국어\t영어\t수학\t총점\t평균" << endl;
	//vector<Student*>::iterator
	for (auto iter = st.begin();  iter != st.end(); ++iter)
	{
		(*iter)->PrintLine();
	}
}

void StudentManager::SaveFile()
{
	FILE* pFile = fopen("save.txt", "w");
	fprintf(pFile, "%d\n", st.size());
	for (auto iter = st.begin(); iter != st.end(); ++iter)
	{
		(*iter)->SaveStudent(pFile);
	}
	fclose(pFile);
}
