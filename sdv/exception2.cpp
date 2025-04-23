#include <iostream>
	
 
struct A {
    int n;
    A(int n = 0): n(n) { std::cout << "A(" << n << ") constructed successfully\n"; }
    ~A() { std::cout << "A(" << n << ") destroyed\n"; }
};
 
int foo()
{
    throw std::runtime_error("sooraj error");
}
 
struct B {
    A a1, a2, a3;
    B() try : a1(1), a2(foo()), a3(3) {
        std::cout << "B constructed successfully\n";
    } catch(...) {
    	std::cout << "B::B() exiting with exception\n";
    }
    ~B() { std::cout << "B destroyed\n"; }
};
 
struct C : A, B {
    C() try {
        std::cout << "C::C() completed successfully\n";
    } catch(...) {
        std::cout << "C::C() exiting with exception\n";
    }
    ~C() { std::cout << "C destroyed\n"; }
};
 
class D {
    D() try {
        std::cout << "D::D() completed successfully\n";
		throw std::runtime_error("sooraj error");
    } catch(...) {
        std::cout << "D::D() exiting with exception\n";
    }
    ~D() { std::cout << "D destroyed\n"; }
	public:
    static D& GetInstance()
    {
        try
        {
            static D obj;
            return obj;
        }
        catch(const std::exception& e)
        {
			std::cout << "Message catched and rethrown" << std::endl;
            std::cerr << e.what() << '\n';
            throw;
        }
    }
};
 
 
int main ()
{
	try
{
    // creates the A base subobject
    // creates the a1 member of B
    // fails to create the a2 member of B
    // unwinding destroys the a1 member of B
    // unwinding destroys the A base subobject
    //C c;
	//D d;
	D::GetInstance();
} catch (const std::exception& e) {
    std::cout << "main() failed to create C with: " << e.what() << std::endl;
}
}