#include <iostream>

class Creature
{
    private:
    std::string m_name;

    public:
        Creature(const std::string &name)
            :  m_name{name}
            //:  m_name{std::move(name)}
    {
	std::cout << "Constructor called" << std::endl;
    }
};

#if 0
Creature(std::string name)
        :  m_name{std::move(name)}
{
}
#endif

int main()
{
    std::string nameString("Alex")
	std::string val;
	std::cin >> val;
    Creature c(nameString);
    //Creature c(std::move(val));
    //Creature c(val);
}



