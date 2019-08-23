#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

//bool Pred(int n)
//{
//	return n <= 30;
//}
//bool Pred(int n)
//{
//	return 30 <= n && n <= 40;
//}
template<typename T>
struct Plus
{
	T operator()(const T& Left, const T& Right)
	{
		return Left + Right;
	}
};
int main()
{

	vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.push_back(5);

	cout << "v : ";
	for (auto i = 0; i < v1.size(); ++i)
	{
		cout << v1[i] << " ";
	}
	cout << endl;
	
	cout << accumulate(v1.begin(), v1.end(), 0, Plus<int>()) << endl;
	cout << accumulate(v1.begin(), v1.end(), 0, plus<int>()) << endl;
	cout << accumulate(v1.begin(), v1.end(), 1, multiplies<int>()) << endl;

	//vector<int> v1;
	//v1.push_back(10);
	//v1.push_back(20);
	//v1.push_back(30);
	//v1.push_back(40);
	//v1.push_back(50);

	//cout << "v : ";
	//for (auto i = 0; i < v1.size(); ++i)
	//{
	//	cout << v1[i] << " ";
	//}
	//cout << endl;

	//random_shuffle(v1.begin(), v1.end());
	//cout << "v1 : ";
	//for (auto i = 0; i < v1.size(); ++i)
	//{
	//	cout << v1[i] << " ";
	//}

	//random_shuffle(v1.begin(), v1.end());
	//cout << "v1 : ";
	//for (auto i = 0; i < v1.size(); ++i)
	//{
	//	cout << v1[i] << " ";
	//}

	/*vector<int> v1;
	v1.push_back(10);
	v1.push_back(20);
	v1.push_back(30);
	v1.push_back(40);
	v1.push_back(50);


	for (auto i = 0; i < v1.size(); ++i)
	{
		cout << v1[i] << " ";
	}
	cout << endl;
	vector<int>::iterator iter_end;
	iter_end = remove_if(v1.begin(), v1.end(), Pred);

	for (auto iter = v1.begin(); iter != iter_end; ++iter)
	{
		cout << *iter << " ";
	}*/
	//cout << endl;
	//cout << "v2 : ";
	//for (auto i = 0; i < v1.size(); ++i)
	//{
	//	cout << v2[i] << " ";
	//}
	//cout << endl;
	//cout << "v3 : ";
	//for (auto i = 0; i < v1.size(); ++i)
	//{
	//	cout << v3[i] << " ";
	//}
	//cout << endl;

	//vector<int>::iterator iter_end;
	//iter_end = replace_if


	return 0;
}