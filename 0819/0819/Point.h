#pragma once
#include <iostream>

using namespace std;

class Point
{
	int x;
	int y;
public:
	explicit Point(int _x = 0, int _y = 0) :x(_x), y(_y) {};
	~Point();

	bool operator==(const Point& arg) const
	{
		return x == arg.x && y == arg.y ? true : false;
	}
	bool operator!=(const Point& arg) const
	{
		return !(*this == arg);
	}
	int operator[](int idx) const
	{
		if (idx == 0)
			return x;
		else if (idx == 1)
			return y;
		else
			throw "이럴수";
	}
	operator int() const
	{
		return x;
	}

	int GetX() const
	{
		return x;
	}

	int GetY() const
	{
		return y;
	}


	void SetX(int _x)
	{
		x = _x;
	}
	void SetY(int _y)
	{
		y = _y;
	}

	void Print() const 
	{ 
		cout << x << ',' << y << endl; 
	}
	static void Print1(int n)
	{
		cout <<"Point 클래스의 정적 맴버 함수 :"<< n << endl;
	}
	void PrintInt(int n)
	{
		cout << "테스트 정수:" << n << endl;
	}
};
//
//const Point operator-(const Point& argL, const Point& argR)
//{
//	return Point(argL.GetX() - argR.GetX, argL.GetY() - argR.GetY());
//}

class PointPtr
{
	Point *ptr;
public:
	PointPtr(Point *p) :ptr(p) {

	}
	~PointPtr()
	{
		delete ptr;
	}
	Point* operator->() const
	{
		return ptr;
	}
	Point& operator*() const
	{
		return *ptr;
	}
};