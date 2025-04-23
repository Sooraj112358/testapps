#include <iostream>
#include <deque>

class Value
{
public:
    int member1;
    int member2;
};


class ValuesContainer
{
private:
    //std::deque<Value> m_vals;

public:
    std::deque<Value> m_vals;
    void add_val1(const Value &val)
    {
		std::cout << "add_val1:" << &val.member1 << std::endl;
        m_vals.push_back( val );
    }

    void add_val2(const Value val)
    {
		std::cout << "add_val2:" << &val.member1 << std::endl;
        m_vals.push_back( val );
    }

    void add_val3(const Value &val)
    {
		std::cout << "add_val3:" << &val.member1 << std::endl;
        m_vals.push_back( Value(val) );
    }

    void add_val4(Value &&val)
    {
		std::cout << "add_val4:" << &val.member1 << std::endl;
        m_vals.push_back( std::move(val) );
    }
};

int main()
{
	ValuesContainer A;
	Value B;
	Value &C=B;
	
	B.member1 = 11;
	B.member1 = 13;

	std::cout << "A:" << &A << " B:" << &B << " C:" << &C << std::endl;

	A.add_val1(B);
	auto r(std::move(A.m_vals.back()));
	std::cout << "m_vals1:" << &r << std::endl;

	A.add_val1(B);
	std::cout << "m_vals1:" << &(A.m_vals.back()) << std::endl;

	A.add_val2(B);
	std::cout << "m_vals2:" << &(A.m_vals.back()) << std::endl;

	A.add_val3(B);
	std::cout << "m_vals3:" << &(A.m_vals.back()) << std::endl;

	A.add_val4(std::move(B));
	std::cout << "m_vals4:" << &(A.m_vals.back()) << std::endl;

    return 0;
}