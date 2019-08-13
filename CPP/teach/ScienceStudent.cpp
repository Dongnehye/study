#include "ScienceStudent.h"
#include <iostream>
using namespace std;

ScienceStudent::ScienceStudent()
{
}


ScienceStudent::~ScienceStudent()
{
}

void ScienceStudent::InputLine(const int iCurStudent)
{
	Student::InputLine(iCurStudent);
	cout << "¼ö2" << endl;
	cin >> math2;
}

float ScienceStudent::GetSum()
{
	return kor + eng + math + math2;
}

void ScienceStudent::PrintLine()
{
	float fSum = GetSum();
	float fAvg = fSum / 4;
	
	Student::PrintLinePre();
	cout << "0" << "\t" << math2 << "\t" << fSum << "\t" << fAvg << endl;
}

void ScienceStudent::LoadStudent(FILE* pFile)
{
	char szBuf[256];
	fscanf(pFile, "%d %s %d %d %d\n", &no, szBuf,
		&kor, &eng, &math);

	szName = szBuf;
}

void ScienceStudent::SaveStudent(FILE* pFile)
{
	fprintf(pFile, "%d %s %d %d %d\n", no, szName.c_str(),
		kor, eng, math);
}
