#include <test.hpp>
#include <cassert>

int main() {
    {
        ft::vector<int> vec;
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);
        assert(vec.back() == 3);
        vec.pop_back();
        assert(vec.back() == 2);
        vec.pop_back();
        assert(vec.back() == 1);
        vec[0] = 4;
        assert(vec.back() == 4);
    }
    return 0;
}
