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
		cout << "operator A() ȣ��" << endl;
		return A();
	}
	operator int()
	{
		cout << "operator int() ȣ��" << endl;
		return 10;
	}
	operator double()
	{
		cout << "operator doulble() ȣ��" << endl;
		return 5.5;
	}
};