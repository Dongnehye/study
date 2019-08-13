#pragma once
#include <stdio.h>
#include <string>
using namespace std;

class Student
{
protected:
	int no;
	string szName;
	int kor;
	int eng;
	int math;

public:
	virtual float GetSum() = 0;

	virtual void LoadStudent(FILE* pFile);
	virtual void SaveStudent(FILE* pFile);
	void PrintLinePre();
	virtual void PrintLine() = 0;
	virtual void InputLine(const int iCurStudent);

	Student();
	virtual ~Student();
};

