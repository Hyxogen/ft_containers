#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <functional>
#include <memory>
#include <test.hpp>

int main() {
    {
        ft::map<int, int> map1;

        for (int i = 0; i < 1000; ++i) {
            map1.insert(ft::map<int, int>::value_type(i, rand()));
        }

        ft::map<int, int> map2(map1.begin(), map1.end(), std::less<int>(),
                               std::allocator<int>());
        assert(std::equal(map1.begin(), map1.end(), map2.begin()));
    }
}
