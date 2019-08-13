#include "Student.h"
#include <iostream>
using namespace std;

Student::Student()
{
}


Student::~Student()
{
}

void Student::InputLine(const int iCurStudent)
{
	no = iCurStudent + 1;
	cout << "이름" << endl;
	cin >> szName;
	cout << "국어" << endl;
	cin >> kor;
	cout << "영어" << endl;
	cin >> eng;
	cout << "수학" << endl;
	cin >> math;
	cout << "문과or이과(0,1)" << endl;
	cin >> math;
}
void Student::PrintLinePre()
{
	cout << no << "\t" << szName << "\t" <<
		kor << "\t" << eng << "\t" <<
		math << "\t";

}
void Student::PrintLine()
{

}

void Student::LoadStudent(FILE* pFile)
{
	char szBuf[256];
	fscanf(pFile, "%d %s %d %d %d %d", &no, szBuf,
		&kor, &eng, &math, &track);

	szName = szBuf;
}

void Student::SaveStudent(FILE* pFile)
{
	fprintf(pFile, "%d %s %d %d %d", no, szName.c_str(),
		kor, eng, math);
}