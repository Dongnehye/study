#include "study.h"

using namespace std;

bool Pred(int n)
{
	return 35 < n;
}
void Print(int n)
{
	cout << n << " ";
}

int main()
{
	vector<int> v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);
	v.push_back(50);

	for_each(v.begin(), v.begin() + 2, Print);
	cout << endl;
	for_each(v.begin(), v.begin() + 4, Print);
	cout << endl;
	for_each(v.begin(), v.end(), Print);
	cout << endl;
	//vector<int> v;
	//v.push_back(10);
	//v.push_back(20);
	//v.push_back(30);
	//v.push_back(40);
	//v.push_back(50);

	//for (vector<int>::size_type i = 0; i < v.size(); ++i)
	//{
	//	cout << v[i] << " ";
	//}
	//cout << endl;

	//vector<int>::iterator iter;

	//iter = find(v.begin(), v.end(), 20);
	//if (iter != v.end())
	//	cout << *iter << "�� ã��" << endl;

	//iter = find_if(v.begin(), v.end(), Pred);
	//if (iter != v.end())
	//	cout << *iter << "���������� 35���� ū ù���� ����: "<< *iter << endl;

	return 0;
}