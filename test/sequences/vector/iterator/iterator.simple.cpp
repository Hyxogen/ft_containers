#include <cassert>
#include <cstddef>
#include <vector.hpp>

int main() {
    {
        ft::vector<int> vec;
        assert(vec.begin() == vec.end());
    }
    {
        ft::vector<int> vec(3, 42);
        assert(vec.begin() != vec.end());
        std::size_t count = 0;
        for (ft::vector<int>::iterator it = vec.begin(); it != vec.end();
             ++it) {
            ++count;
            assert(*it == 42);
            *it /= 2;
        }
        assert(count == 3);
        for (ft::vector<int>::iterator it = vec.begin(); it != vec.end();
             ++it) {
            assert(*it == 21);
        }
    }
    {
        ft::vector<int> vec(5, 54321);
        assert(vec.begin() != vec.end());
        for (ft::vector<int>::const_iterator it = vec.begin(); it != vec.end();
             ++it) {
            assert(*it == 54321);
        }
    }
    return 0;
}
