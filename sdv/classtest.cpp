#include <iostream>
#include <memory>
#include <unistd.h>
#include <mutex>

using namespace std;

class OtherClass {
public:
    OtherClass(string x){cout<<"OtherClass C->"<<endl;};
    ~OtherClass() {cerr<<"OtherClass D->"<<endl;};
};

class MyClass {
public:
    MyClass(string x) : name(x), D("test"), E("nest"){cout<<"MyClass C->"<<name<<endl;};
    ~MyClass() {cerr<<"MyClass D->"<<name<<endl;};
    string name;
	OtherClass D, E;
};


int main(void) {
#if 0
	MyClass T = MyClass("A");
	{
		MyClass B =  T;
	}
	

	shared_ptr<MyClass> S = make_shared<MyClass>("A");
	{
		shared_ptr<MyClass> B =  S;
	}
#endif
	{
	unique_ptr<MyClass> U( new MyClass("A"));
	unique_ptr<MyClass> U1 =  std::move(U);
	shared_ptr<MyClass> U2 =  std::move(U);
	}

	sleep(5);

    return 0;
}
