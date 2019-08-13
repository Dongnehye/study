#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

//template <typename T> T sum(T a, T b)
//{
//	return a + b;
//}

class POINT
{
public:
	int x;
	int y;
	
	POINT operator+(POINT& right)
	{
		x += right.x;
		y += right.y;
		return *this;
	}
};

int main()
{
	//map<int, string> map;
	///*
	//	pair<int, string> p;
	//	p.first = 1;
	//	p.second = "asd";
	//	map.insert(p);
	//*/
	//map.insert(make_pair(1, "asd"));

	//POINT a, b;
	//POINT c;

	//c = a + b;



	return 0;
}