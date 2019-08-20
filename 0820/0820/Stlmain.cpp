#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <stack>

using namespace std;

bool Less(int& l, int& r)
{
	return l < r;
}


int main()
{

	vector<int> v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);
	v.push_back(50);

	vector<int>::iterator iter;
	vector<int>::iterator iter2;
	for (iter = v.begin(); iter != v.end(); ++iter)
		cout << *iter << " ";
	cout << endl;

	iter = v.begin() + 2;
	iter2 = v.erase(iter);
	for (iter = v.begin(); iter != v.end(); ++iter)
		cout << *iter << " ";
	cout << endl;
	iter2 = v.erase(v.begin() + 1, v.end());
	for (iter = v.begin(); iter != v.end(); ++iter)
		cout << *iter << " ";
	cout << endl;

	//for (auto iter = v.begin(); iter != v.end(); ++iter)
	//{
	//	cout << *iter << " ";
	//}
	//cout << endl;

	//vector<int>::reverse_iterator riter(v.rbegin());
	//for (; riter != v.rend(); ++riter)
	//{
	//	cout << *riter << " ";
	//}
	//cout << endl;


	/*stack<int> st;

	st.push(10);
	st.push(20);
	st.push(30);

	cout << st.top() << endl;
	st.pop();
	cout << st.top() << endl;
	st.pop();
	cout << st.top() << endl;
	st.pop();

	if (st.empty())
		cout << "stack 에 데이터가 없음." << endl;*/

	//int a = 10;
	//vector<int> v;
	//v.push_back(10);
	//v.push_back(20);
	//v.push_back(30);
	//v.push_back(40);
	//v.push_back(50);

	////sort(v.begin(), v.end(), less<int>());
	////for (auto iter = v.begin(); iter != v.end(); ++iter)
	////{
	////	cout << *iter << endl;
	////}
	////cout << endl;
	//sort(v.begin(), v.end(), [](int& l, int& r) 
	//	-> bool {return l < r; });
	//for (auto iter = v.begin(); iter != v.end(); ++iter)
	//{
	//	cout << *iter << endl;
	//}
	//cout << endl;
	//sort(v.begin(), v.end(), greater<int>());
	//for (auto iter = v.begin(); iter != v.end(); ++iter)
	//{
	//	cout << *iter << endl;
	//}
	//cout << endl;
	//return 0;
}