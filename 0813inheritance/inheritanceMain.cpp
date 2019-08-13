#include <iostream>
#include <vector>

using namespace std;

class parent
{
protected:
	int a = 0;
public:
	virtual void print() = 0;
	virtual void printAAA()
	{
		cout << a << endl;
	}
};

class child1 : public parent
{
private:
	int c = 10;
public:
	virtual void print()
	{
		parent::printAAA();
		cout << c << endl;
	}
};

class child2 : public parent
{
private:
	int d = 12;
public:
	virtual void print()
	{
		cout << d << endl;
	}
	void printAll()
	{
		cout << "printAll" << endl;
	}
};


int main()
{
	vector<parent*> vec;
	child1 c;

	vec.push_back(new child1());
	vec.push_back(new child2());

	for (auto iter = vec.begin(); iter != vec.end(); ++iter)
	{
		//child2* pCh = (child2*)(*iter); // 다운 캐스트.
		child2* pCh =  dynamic_cast<child2*>(*iter); // 다운 캐스트.
		if (pCh)
		{
			pCh->printAll();
		}
		(*iter)->print();
	}

	return 0;
}