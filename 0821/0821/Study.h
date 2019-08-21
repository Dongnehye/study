#pragma once
#include <deque>
#include <list>
#include <set>
#include <map>

using namespace std;
bool Predicate(int first, int second)
{
	return second - first <= 0;
}

void listFunc()
{
	list<int> lt;

	lt.push_back(10);
	lt.push_back(10);
	lt.push_back(20);
	lt.push_back(30);
	lt.push_back(30);
	lt.push_back(30);
	lt.push_back(40);
	lt.push_back(50);
	lt.push_back(10);

	list<int>::iterator iter;
	for (iter = lt.begin(); iter != lt.end(); ++iter)
		cout << *iter << ' ';
	cout << endl;

	lt.unique(Predicate);

	for (iter = lt.begin(); iter != lt.end(); ++iter)
		cout << *iter << ' ';
	cout << endl;
	//list<int> lt;
	//list<int> lt2;

	//lt.push_back(10);
	//lt.push_back(20);
	//lt.push_back(30);
	//lt.push_back(40);
	//lt.push_back(50);

	//lt2.push_back(100);
	//lt2.push_back(200);
	//lt2.push_back(300);
	//lt2.push_back(400);
	//lt2.push_back(500);

	//list<int>::iterator iter;
	//cout << "lt1: ";
	//for (iter = lt.begin(); iter != lt.end(); ++iter)
	//	cout << *iter << ' ';
	//cout << endl;

	//cout << "lt2: ";
	//for (iter = lt2.begin(); iter != lt2.end(); ++iter)
	//	cout << *iter << ' ';
	//cout <<"==================================" <<endl;

	//iter = lt.begin();
	//++iter;
	//++iter;

	//lt.splice(iter, lt2);
	//cout << "lt1: ";
	//for (iter = lt.begin(); iter != lt.end(); ++iter)
	//	cout << *iter << ' ';
	//cout << endl;

	//cout << "lt2: ";
	//for (iter = lt2.begin(); iter != lt2.end(); ++iter)
	//	cout << *iter << ' ';
	//cout << endl;
	//list<int> lt;

	//lt.push_back(10);
	//lt.push_back(20);
	//lt.push_back(30);
	//lt.push_back(10);
	//lt.push_back(40);
	//lt.push_back(50);
	//lt.push_back(10);
	//lt.push_back(10);

	//list<int>::iterator iter;
	//for (iter = lt.begin(); iter != lt.end(); ++iter)
	//	cout << *iter << ' ';
	//cout << endl;

	//lt.remove(10);

	//for (iter = lt.begin(); iter != lt.end(); ++iter)
	//	cout << *iter << ' ';
	//cout << endl;
	//list<int> lt;

	//lt.push_back(10);
	//lt.push_back(20);
	//lt.push_back(30);
	//lt.push_back(40);
	//lt.push_back(50);

	//list<int>::iterator iter;
	//for (iter = lt.begin(); iter != lt.end(); ++iter)
	//	cout << *iter << ' ';
	//cout << endl;

	//lt.push_front(100);
	//lt.push_front(200);

	//for (iter = lt.begin(); iter != lt.end(); ++iter)
	//	cout << *iter << ' ';
	//cout << endl;
	//deque<int> dq;

	//dq.push_back(10);
	//dq.push_back(20);
	//dq.push_back(30);
	//dq.push_back(40);
	//dq.push_back(50);

	//for (deque<int>::size_type i = 0; i < dq.size(); ++i)
	//{
	//	cout << dq[i] << " ";
	//}
	//cout << endl;

	//dq.push_front(100);
	//dq.push_front(200);

	//for (deque<int>::size_type i = 0; i < dq.size(); ++i)
	//{
	//	cout << dq[i] << " ";
	//}
	//cout << endl;

}


void setFunc()
{
	set<int> s;

	s.insert(50);
	s.insert(30);
	s.insert(80);
	s.insert(40);
	s.insert(10);
	s.insert(70);
	s.insert(90);

	set<int>::iterator iter;
	for (iter = s.begin(); iter != s.end(); ++iter)
	{
		cout << *iter << " ";
	}
	cout << endl;

	set<int>::iterator iter_lower;
	set<int>::iterator iter_upper;

	iter_lower = s.lower_bound(30);
	iter_upper = s.upper_bound(30);
	cout << *iter_lower << endl;
	cout << *iter_upper << endl;

	iter_lower = s.lower_bound(55);
	iter_upper = s.upper_bound(55);
	if (iter_lower != iter_upper)
		cout << "55잇" << endl;
	else
		cout << "55없" << endl;

	//set<int> s;

	//s.insert(50);
	//s.insert(30);
	//s.insert(80);
	//s.insert(40);
	//s.insert(10);
	//s.insert(70);
	//s.insert(90);

	//set<int>::iterator iter;
	//for (iter = s.begin(); iter != s.end(); ++iter)
	//{
	//	cout << *iter << " ";
	//}
	//cout << endl;

	//iter = s.find(30);

	//if (iter != s.end())
	//	cout << *iter << "가 s에 있다!" << endl;
	//else
	//	cout << "30이 s에 없다!" << endl;


	//set<int> s;

	//s.insert(50);
	//s.insert(30);
	//s.insert(80);
	//s.insert(40);
	//s.insert(10);
	//s.insert(70);
	//s.insert(90);

	//set<int>::iterator iter;
	//for (iter = s.begin(); iter != s.end(); ++iter)
	//{
	//	cout << *iter << " ";
	//}
	//cout << endl;

	//s.insert(50);
	//s.insert(50);

	//for (iter = s.begin(); iter != s.end(); ++iter)
	//{
	//	cout << *iter << " ";
	//}

}