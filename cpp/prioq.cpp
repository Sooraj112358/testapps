#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

using namespace std;

template<typename T> void print_queue(T& q) {
    cout << "Queue:" << endl;
    while(!q.empty()) {
        vector<int> tmp;
        tmp = q.top();
        std::cout << tmp[0] << ":" << tmp[1] << ":" << tmp[2] << ":" << tmp[3] << endl;
        q.pop();
    }
    std::cout << '\n';
}


struct my_comparator
{
    // queue elements are vectors so we need to compare those
    bool operator()(std::vector<int> const& a, std::vector<int> const& b) const
    {
        // sanity checks
        assert(a.size() == 4);
        assert(b.size() == 4);
        std::cout << a[2] << ":" << b[2] << endl;
        // reverse sort puts the lowest value at the top
        return a[2] > b[2];
    }
};

// for usability wrap this up in a type alias:
using my_priority_queue = std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, my_comparator>;

int main()
{
    my_priority_queue mpq;

    mpq.push({1, 2, 1, 4});
    mpq.push({1, 2, 2, 4});
    mpq.push({1, 2, 3, 4});
    mpq.push({1, 2, 4, 4});
    mpq.push({1, 2, 5, 4});

    print_queue(mpq);

    return 0;
}
