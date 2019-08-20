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
	// 복사가 일어나면 안되는 애. 소유권이 확실한 하나의 객체만 쓰면 된다.
	unique_ptr<TestClass> uptr(new TestClass());
	unique_ptr<TestClass> uptr2 = move(uptr);

	//shared_ptr<TestClass> sptr3(new TestClass[10], default_delete<TestClass>());
	// delete 쓰기 깜박할때 사용하면된다.
	// 상호 참조 하게되면 해제가 되지않는 경우가 생김.
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