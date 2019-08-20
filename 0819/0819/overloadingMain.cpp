#include <iostream>
#include <algorithm>
#include "Point.h"
#include "Array.h"
#include "A.h"
#include "String.h"

template<typename RetType, typename ArgType>
struct Pair
{
	T1 first;
	T2 second;
	Pair(const T1& ft, const T2& sd) :first(ft), second(sd) {
	}
};

template<typename RetType, typename ArgType>
class Functor
{
public:
	RetTpye operator()(ArgType data)
	{
		cout << data << endl;
		return ReType;
	}
};

template<typename IterT, typename Func>
void For_each(IterT begin, IterT end, Func pf)
{
	while (begin != end)
	{
		pf(*begin++);
	}
}
void PrintInt(int data)
{
	cout << data << " ";
}
void PrintStirng(string data)
{
	cout << data << " ";
}

template<typename T>
class ObjectInfo
{
	T data;
public:
	ObjectInfo(const T& d):data(d){}

	void Print()
	{
		cout << "타입 : " << typeid(data).name() << endl;
		cout << "크기 : " << sizeof(data) << endl;
		cout << "값 : " << data << endl;
		cout <<  endl;
	}
};

template<typename T>
void Print(T a)
{
	cout << a << endl;
}
template< >
void Print(Point a)
{
	cout << "Print 특수화 버전 : ";
	a.Print();
}

template<typename T>
void Swap(T &a, T &b)
{
	T temp = a;
	a = b;
	b = temp;
}

template<typename T1, typename T2>
void Print(T1 a, T2 b)
{
	cout << a << "," << b << endl;
}

bool Pred_less(int a, int b)
{
	return a < b;
}
struct Less
{
	bool operator()(int a, int b)
	{
		return a < b;
	}
};

struct Functor1
{
	void operator()(int n)
	{
		cout << n << " ";
	}
};
struct Functor2
{
	void operator()(int n)
	{
		cout << n*n << " ";
	}
};
struct Functor3
{
	void operator()(int n)
	{
		cout << "정수 : " << n << endl;
	}
};


//void Print1(int n)
//{
//	cout << n << ' ';
//}
//void Print2(int n)
//{
//	cout << n*n << " ";
//}
//void Print3(int n)
//{
//	cout << "정수 : "<<n << endl;
//}



//struct FuncObject
//{
//public:
//	void operator()(int args)const
//	{
//		cout << "정수 : " << args << endl;
//	}
//};
//
//void Print1(int arg)
//{
//	cout << "정수 : " << arg << endl;
//}
//
//void Print(int n)
//{
//	cout << "전역 함수:"<< n << endl;
//}
//
//namespace NA
//{
//	void Print(int n)
//	{
//		cout << "전역 함수:" << n << endl;
//	}
//}

int main()
{
	Pair<int, int> p1(10, 20);
	//Functor<void, int> functor1;
	//functor1(10);
	//Functor<bool, string> functor2;
	//functor2("Hello");

//	int arr[5] = { 10, 20, 30, 40, 50 };
//
//	for_each(arr, arr + 5, PrintInt);
//	cout << endl;
//	string arr1[3] = { "abc","ABC","Hello!" };
//
//	for_each(arr1, arr1 + 3, PrintStirng);

	//ObjectInfo<int> d1(10);
	//d1.Print();

	//ObjectInfo<double> d2(10);
	//d2.Print();

	//ObjectInfo<string> d3("hoe");
	//d3.Print();


	//Array<int> iarr;
	//iarr.Add(10);
	//iarr.Add(20);
	//iarr.Add(30);

	//Array<double> darr;
	//darr.Add(20);
	//darr.Add(30);
	//darr.Add(10);

	//Array<string> sarr;
	//sarr.Add("abc");
	//sarr.Add("ABC");
	//sarr.Add("Hello!");

	//for (int i = 0; i < sarr.GetSize(); ++i)
	//{
	//	cout << sarr[i] << " ";
	//}

	//int n = 10;
	//double d = 2.5;
	//Point pt(2, 3);

	//Print(n);
	//Print(d);
	//Print(pt);


	//Print(10, 1.5);
	//Print("Hello!", 100);
	//Print(1.5, "Hello!");

	//Less l;

	//cout << Pred_less(10, 20) << endl;
	//cout << Pred_less(20, 10) << endl;
	//cout << endl;
	//cout << l(10, 20) << endl;
	//cout << l(20, 10) << endl;
	//cout << Less()(10, 20) << endl;
	//cout << Less()(20, 10) << endl;
	//cout << endl;
	//cout << l.operator()(10,20)<< endl;
	//cout << Less().operator()(10,20)<< endl;



	//int arr[5] = { 10, 20, 30, 40, 50 };

	//for_each(arr, arr + 5, Functor1());
	//cout << endl << endl;
	//for_each(arr, arr + 5, Functor2());
	//cout << endl << endl;
	//for_each(arr, arr + 5, Functor3());
	//void(*pf)(int);

	//Print1(10);
	//NA::Print(10);
	//Point::Print1(10);
	//pf = Print;
	//pf(10);
	//pf = NA::Print;
	//pf(10);
	//pf = Point::Print1;
	//pf(10);
	

	/*Point* p1 = new Point(2, 3);
	PointPtr p2 = new Point(5, 5);

	p1->Print();
	p2->Print();
	cout << endl;

	(*p1).Print();
	(*p2).Print();

	delete p1;*/

	//Point pt;
	//pt.Print();
	////pt = 10;
	//pt = Point(10);

	//pt.Print();

	/*int n = 10;
	Point pt(2, 3);
	n = pt;
	cout << n << endl;*/

	/*String s("Hello!");
	const char* sz = s;*/
	//String s("Hi!");
	//const char* sz = "Hello";

	//s = sz;

	//sz = nullptr;

	//Point pt(2, 3);
	//Point *p = &pt;

	//void(Point::*pf1)()const;
	//pf1 = &Point::Print;

	//void(Point::*pf2)(int);
	//pf2 = &Point::PrintInt;

	//pt.Print();
	//pt.PrintInt(10);

	//(pt.*pf1)();
	//(pt.*pf2)(10);

	//(p->*pf1)();
	//(p->*pf2)(10);

	return 0;
}