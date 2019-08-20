#include <iostream>
#include <vector>
#include <memory>
#include "TestClass.h"
using namespace std;

int main()
{
	////auto_ptr<TestClass>();
	//auto_ptr<TestClass> uptr(new TestClass());
	//auto_ptr<TestClass> uptr2 = uptr;
	// ���簡 �Ͼ�� �ȵǴ� ��. �������� Ȯ���� �ϳ��� ��ü�� ���� �ȴ�.
	unique_ptr<TestClass> uptr(new TestClass());
	unique_ptr<TestClass> uptr2 = move(uptr);

	//shared_ptr<TestClass> sptr3(new TestClass[10], default_delete<TestClass>());
	// delete ���� �����Ҷ� ����ϸ�ȴ�.
	// ��ȣ ���� �ϰԵǸ� ������ �����ʴ� ��찡 ����.
	vector<shared_ptr<TestClass>> vec;
	vec.push_back(make_shared<TestClass>());
	//shared_ptr<TestClass> sptr1(new TestClass());
	shared_ptr<TestClass> sptr1 = make_shared<TestClass>();
	shared_ptr<TestClass> sptr2 = sptr1;
	//sptr1->a = 10;
	
	weak_ptr<TestClass> wptr1 = sptr1;

	cout << sptr1.use_count() << endl;
	return 0;
}