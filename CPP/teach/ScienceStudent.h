#pragma once
#include "Student.h"

class ScienceStudent : public Student
{
private:
	int math2;
public:
	virtual void LoadStudent(FILE* pFile);
	virtual void SaveStudent(FILE* pFile);
	virtual void PrintLine();
	virtual float GetSum();
	virtual void InputLine(const int iCurStudent);

	ScienceStudent();
	virtual ~ScienceStudent();
};

