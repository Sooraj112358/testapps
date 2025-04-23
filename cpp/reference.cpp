
#include <iostream>

int& GetValue(int i)
{
    static int val = i;
    return val;
}

main()
{
    int test = GetValue(11);
    std::cout << "test:" << test << std::endl;
    GetValue(33) = 22;
    std::cout << "test:" << test << std::endl;
}
