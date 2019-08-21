#include "ScienceStudent.h"



ScienceStudent::ScienceStudent()
{
}


ScienceStudent::~ScienceStudent()
{
}

void ScienceStudent::LoadStudent(FILE * pFile)
{
	Student::LoadStudent(pFile);
	fscanf(pFile, "%d\n", &science);
}

void ScienceStudent::SaveStudent(FILE * pFile)
{
	Student::SaveStudent(pFile);
	fprintf(pFile, " %d\n", science);
}

float ScienceStudent::GetSum()
{
	return kor + eng + math;
}

void ScienceStudent::PrintLine()
{
	float fSum = kor + eng + math;
	float fAvg = fSum / 4;

	Student::PrintLinePre();

	cout << "0" <<"\t" << science << fSum << "\t" << fAvg << endl;
}

void ScienceStudent::InputLine(const int iCurStudent)
{
	Student::InputLine(iCurStudent);
	cout << "°úÇÐ" << endl;
	cin >> science;
}