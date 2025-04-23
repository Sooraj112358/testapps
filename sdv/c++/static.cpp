#include<iostream>

#if 1
struct Entity
{
	private:
	void print()
	{
		std::cout << x << " , " << y << std::endl;
	}
	static int x,y;
};
#else

class Entity
{
	public:
	void print()
	{
		std::cout << x << " , " << y << std::endl;
	}
	static int x,y;
};
#endif
int Entity::x;
int Entity::y;

int main()
{
	Entity e;
	e.x = 5;
	e.y = 8;

	e.print();
}
