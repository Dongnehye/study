#pragma once
#include "Student.h"
class NAStudent : public Student
{
private:
	int history;
public:
	virtual void LoadStudent(FILE* pFile);
	virtual void SaveStudent(FILE* pFile);
	virtual void PrintLine();
	virtual float GetSum();
	virtual void InputLine(const int iCurStudent);

	NAStudent();
	virtual ~NAStudent();
};

