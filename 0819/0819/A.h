#pragma once

#include <iostream>

using namespace std;
class A
{
};

class B
{
public:
	operator A()
	{
		cout << "operator A() 호출" << endl;
		return A();
	}
	operator int()
	{
		cout << "operator int() 호출" << endl;
		return 10;
	}
	operator double()
	{
		cout << "operator doulble() 호출" << endl;
		return 5.5;
	}
};