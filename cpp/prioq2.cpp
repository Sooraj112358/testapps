#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

using namespace std;

template<typename T> void print_queue(T& q) {
    while(!q.empty()) {
        int tmp;
        tmp = q.top();
        std::cout << tmp[0] << ", ";
        q.pop();
    }
    std::cout << '\n';
}


struct my_comparator
{
    // queue elements are vectors so we need to compare those
    bool operator()(int const& a, int const& b) const
    {
        // sanity checks
        assert(a.size() == 4);
        assert(b.size() == 4);

        // reverse sort puts the lowest value at the top
        return a > b[0];
    }
};

// for usability wrap this up in a type alias:
using my_priority_queue = std::priority_queue<int, std::vector<int>, my_comparator>;

int main()
{
    my_priority_queue mpq;

    mpq.push({5, 1, 4});
    mpq.push({2, 1, 1});
    mpq.push({4, 2, 2});

    print_queue(mpq);

    return 0;
}
