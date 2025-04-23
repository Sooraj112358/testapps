#include <iostream>
int global{};
int& foo()
{
   return global;
}

int main()
{
    decltype(foo()) a = foo(); //a is an `int&`
    auto b = foo(); //b is an `int`
    b = 2;

    std::cout << "a: " << a << '\n'; //prints "a: 0"
    std::cout << "b: " << b << '\n'; //prints "b: 2"

    std::cout << "---\n";
    decltype(foo()) c = foo(); //c is an `int&`
    c = 10;

    std::cout << "a: " << a << '\n'; //prints "a: 10"
    std::cout << "b: " << b << '\n'; //prints "b: 2"
    std::cout << "c: " << c << '\n'; //prints "c: 10"
 }