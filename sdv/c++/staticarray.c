#include<iostream>

#define MAX_ENTRY 11

using namespace std;

enum val{
	one = 1,
	five = 5,
	nine = 9,
	eleven = 11
};
typedef struct
{
  string name;
  string b;
}my_data;

my_data data[MAX_ENTRY] =
{
  [0] = { .name = "Peter" , .b = "surname"},
  [1] = { .name = "James" , .b = "surname"},
  [2] = { .name = "John" , .b = "surname"},
  [4] = { .name = "Mike" , .b = "surname"}
};

int main()
{
	for(int i = 0; i < MAX_ENTRY; i++)
		cout <<"val: " << i << " name: " << data[i].name << std::endl;
	
	return 0;
}
