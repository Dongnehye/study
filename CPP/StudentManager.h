#pragma once
#include "Student.h"
#include <vector>
#include "ScienceStudent.h"
#include "LiberalStudent.h"

using namespace std;

enum track
{
	liberal,
	sciences
};

class StudentManager
{
private:
	vector<Student*> st;
public:

	void LoadFile();
	void InputStudent();
	void OutputStudent();
	void SaveFile();
	void PrintMenu();

	StudentManager();
	virtual ~StudentManager();
};

