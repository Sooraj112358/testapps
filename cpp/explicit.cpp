#include<iostream>

class MyClass {
public:
    //MyClass(int x) { 
    explicit MyClass(int x) { 
        std::cout << "Constructor with int: " << x << std::endl;
    }
};

void someFunction(MyClass obj) {
    // some code
}

int main() {
    someFunction(42);  // Implicit conversion from int to MyClass
}

