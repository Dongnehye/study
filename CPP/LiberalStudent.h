#pragma once
#include "Student.h"

class LiberalStudent :
	public Student
{
private:
	int history;

public:
	LiberalStudent();
	virtual ~LiberalStudent();

	virtual void LoadStudent(FILE* pFile);
	virtual void SaveStudent(FILE* pFile);
	virtual float GetSum();
	virtual void PrintLine();
	virtual void InputLine(const int iCurStudent);
};