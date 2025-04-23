#include<iostream>

int& GetValue()
{
	static int i = 2;
	return i;
}

int main()
{
	int i = GetValue();
	std::cout << "Val:" << i << std::endl;
	GetValue() = 5;
	i = GetValue();
	std::cout << "Val:" << i << std::endl;
}
