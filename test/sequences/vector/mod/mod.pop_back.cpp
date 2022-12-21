#include <test.hpp>
#include <cassert>
#include <classes.hpp>
#include <cstddef>

int main() {
    {
        ft::vector<int> vec(1);

        vec.pop_back();
        assert(vec.size() == 0);
        assert(vec.capacity() == 1);
    }
    {
        ft::vector<int> vec;
        vec.reserve(2);

        vec.push_back(42);
        vec.push_back(21);

        const ft::vector<int>::iterator it = vec.begin();
        vec.pop_back();
        assert(vec.size() == 1);
        assert(vec[0] == 42);
        assert(vec.begin() == it);
    }
    {
        typedef test::tracking_class clazz;
        ft::vector<clazz> vec(30);

        const std::size_t count = clazz::instances();
        vec.pop_back();
        assert(clazz::instances() == count - 1);
        vec.pop_back();
        assert(clazz::instances() == count - 2);
    }
    {
        ft::vector<int> vec(100);

        for (size_t idx = 0; idx < 100; ++idx) {
            assert(vec.size() == 100 - idx);
            vec.pop_back();
            assert(vec.size() == 99 - idx);
        }
    }
    return 0;
}
