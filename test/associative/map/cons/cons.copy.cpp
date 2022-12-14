#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iterators.hpp>
#include <test.hpp>

int main() {
    {
        ft::map<int, int> map1;

        for (int i = 0; i < 1000; ++i) {
            map1.insert(ft::map<int, int>::value_type(rand(), rand()));
        }

        const ft::map<int, int> map2(map1);
        assert(std::equal(map1.begin(), map1.end(), map2.begin()));
    }
}
