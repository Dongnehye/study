#include "LiberalStudent.h"

using namespace std;

LiberalStudent::LiberalStudent()
{
}

LiberalStudent::~LiberalStudent()
{
}
void LiberalStudent::LoadStudent(FILE* pFile)
{
	Student::LoadStudent(pFile);
	fscanf(pFile, "%d\n", &history);

}
void LiberalStudent::SaveStudent(FILE* pFile) 
{
	Student::SaveStudent(pFile);
	fprintf(pFile, " %d\n", history);
}
float LiberalStudent::GetSum()
{
	return kor + eng + math;
}

void LiberalStudent::PrintLine()
{
	float fSum = kor + eng + math;
	float fAvg = fSum / 4;

	Student::PrintLinePre();

	cout << history << "\t" << "0" << fSum << "\t" << fAvg << endl;
}
void LiberalStudent::InputLine(const int iCurStudent)
{
	Student::InputLine(iCurStudent);
	cout << "¿ª»ç" << endl;
	cin >> history;
}