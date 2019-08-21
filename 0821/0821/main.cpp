#include <iostream>
#include "Study.h"

using namespace std;


int main()
{
	map<int, int> m;
	m[5] = 100;
	m[3] = 100;
	m[8] = 30;
	m[4] = 40;
	m[1] = 70;
	m[7] = 100;
	m[9] = 50;


	map<int, int>::iterator iter;
	for (iter = m.begin(); iter != m.end(); ++iter)
	{
		cout << "(" << (*iter).first << ',' << (*iter).second << ")" << " ";
	}
	cout << endl;
	m[5] = 200;

	for (iter = m.begin(); iter != m.end(); ++iter)
	{
		cout << "(" << iter->first << ',' << iter->second << ")" << " ";
	}
	cout << endl;

	//map<int, int> m;
	//m.insert(pair<int, int>(5, 100));
	//m.insert(pair<int, int>(3, 100));
	//m.insert(pair<int, int>(8, 30));
	//m.insert(pair<int, int>(4, 40));
	//m.insert(pair<int, int>(1, 70));
	//m.insert(pair<int, int>(7, 100));

	//pair<int, int> pr(9, 50);
	//m.insert(pr);
	//map<int, int>::iterator iter;
	//for (iter = m.begin(); iter != m.end(); ++iter)
	//{
	//	cout << "(" << (*iter).first << ',' << (*iter).second << ")" << " ";
	//}
	//cout << endl;

	//for (iter = m.begin(); iter != m.end(); ++iter)
	//{
	//	cout << "(" << iter->first << ',' << iter->second << ")" << " ";
	//}
	//cout << endl;

	//listFunc();
	//setFunc();
	return 0;
}