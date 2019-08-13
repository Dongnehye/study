#pragma once
#include "Student.h"

class ScienceStudent :
	public Student
{
public:
	int science;

	ScienceStudent();
	virtual ~ScienceStudent();

	virtual void LoadStudent(FILE* pFile);
	virtual void SaveStudent(FILE* pFile);
	virtual float GetSum();
	virtual void PrintLine();
	virtual void InputLine(const int iCurStudent);
};

