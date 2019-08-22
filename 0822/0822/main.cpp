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
	//	cout << *iter << "을 찾다" << endl;

	//iter = find_if(v.begin(), v.end(), Pred);
	//if (iter != v.end())
	//	cout << *iter << "순차열에서 35보다 큰 첫번쨰 원소: "<< *iter << endl;

	return 0;
}