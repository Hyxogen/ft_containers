#include <cassert>
#include <vector.hpp>

/* TODO write these tests with proper sequences */
int main() {
    {
        ft::vector<int> vec;
        assert(vec.rbegin() == vec.rend());
    }
    {
        ft::vector<int> vec(300, 42);
        assert(vec.rbegin() != vec.rend());
        std::size_t count = 0;
        for (ft::vector<int>::reverse_iterator it = vec.rbegin();
             it != vec.rend(); ++it) {
            ++count;
            assert(*it == 42);
            *it /= 2;
        }
        assert(count == 300);
        for (ft::vector<int>::reverse_iterator it = vec.rbegin();
             it != vec.rend(); ++it) {
            assert(*it == 21);
        }
    }
    {
        ft::vector<int> vec;
        vec.push_back(5);
        vec.push_back(11);
        vec.push_back(17);
        vec.push_back(21);

        ft::vector<int>::reverse_iterator it = vec.rbegin();
        assert(*it++ == 21);
        assert(*it++ == 17);
        assert(*it++ == 11);
        assert(*it++ == 5);
        assert(it == vec.rend());
    }
    return 0;
}
