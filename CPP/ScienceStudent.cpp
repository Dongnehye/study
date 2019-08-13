#include "ScienceStudent.h"



ScienceStudent::ScienceStudent()
{
}


ScienceStudent::~ScienceStudent()
{
}

void ScienceStudent::LoadStudent(FILE * pFile)
{
}

void ScienceStudent::SaveStudent(FILE * pFile)
{
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
}
