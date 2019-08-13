#include "NAStudent.h"
#include <iostream>
using namespace std;

NAStudent::NAStudent()
{
}


NAStudent::~NAStudent()
{
}


void NAStudent::InputLine(const int iCurStudent)
{
	Student::InputLine(iCurStudent);
	cout << "¿ª»ç" << endl;
	cin >> history;
}

float NAStudent::GetSum()
{
	return kor + eng + math + history;
}

void NAStudent::PrintLine()
{
	float fSum = GetSum();
	float fAvg = fSum / 4;

	Student::PrintLinePre();
	cout << history << "\t" << "0" << "\t" << fSum << "\t" << fAvg << endl;
}

void NAStudent::LoadStudent(FILE* pFile)
{
	char szBuf[256];
	fscanf(pFile, "%d %s %d %d %d\n", &no, szBuf,
		&kor, &eng, &math);

	szName = szBuf;
}

void NAStudent::SaveStudent(FILE* pFile)
{
	Student::SaveStudent(pFile);

	fprintf(pFile, " %d", history);
}