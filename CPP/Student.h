#pragma once
#include <stdio.h>
#include <string>
#include <iostream>

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
	int track;
	virtual void LoadStudent(FILE* pFile);
	virtual void SaveStudent(FILE* pFile);
	virtual void PrintLine() = 0;
	virtual void InputLine(const int iCurStudent);
	void PrintLinePre();
	virtual float GetSum() = 0;

	Student();
	virtual ~Student();
};

