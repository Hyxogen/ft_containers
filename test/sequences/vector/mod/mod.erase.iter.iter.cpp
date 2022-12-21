#include <cassert>
#include <classes.hpp>
#include <string>
#include <vector.hpp>

int main() {
    {
        ft::vector<int> vec;
        for (int i = 0; i < 10; ++i) {
            vec.push_back(i);
        }
        const std::size_t cap = vec.capacity();
        ft::vector<int>::const_iterator it = vec.erase(vec.begin(), vec.end());
        assert(it == vec.begin());
        assert(vec.size() == 0);
        assert(vec.capacity() == cap);
    }
    {
        ft::vector<int> vec;
        for (int i = 0; i < 10; ++i) {
            vec.push_back(i);
        }
        const std::size_t cap = vec.capacity();
        assert(vec.erase(vec.end(), vec.end()) == vec.end());
        assert(vec.size() == 10);
        assert(vec.capacity() == cap);
        for (int i = 0; i < 10; ++i) {
            assert(vec[static_cast<unsigned int>(i)] == i);
        }
    }
    {
        ft::vector<int> vec;
        for (int i = 0; i < 10; ++i) {
            vec.push_back(i);
        }
        const std::size_t cap = vec.capacity();
        ft::vector<int>::const_iterator it =
            vec.erase(vec.begin(), vec.begin() + 1);
        assert(it == vec.begin());
        assert(vec.size() == 9);
        assert(vec.capacity() == cap);
        for (int i = 0; i < 9; ++i) {
            assert(vec[static_cast<unsigned int>(i)] == (i + 1));
        }
    }
    {
        ft::vector<int> vec;
        for (int i = 0; i < 10; ++i) {
            vec.push_back(i);
        }
        const std::size_t cap = vec.capacity();
        ft::vector<int>::const_iterator it =
            vec.erase(vec.begin() + 9, vec.end());
        assert(it == vec.begin() + 9);
        assert(vec.size() == 9);
        assert(vec.capacity() == cap);
        for (int i = 0; i < 9; ++i) {
            assert(vec[static_cast<unsigned int>(i)] == i);
        }
    }
    {
        ft::vector<int> vec;
        for (int i = 0; i < 10; ++i) {
            vec.push_back(i);
        }
        const std::size_t cap = vec.capacity();
        ft::vector<int>::const_iterator it =
            vec.erase(vec.begin() + 2, vec.begin() + 4);
        assert(it == vec.begin() + 2);
        assert(vec.size() == 8);
        assert(vec.capacity() == cap);
        for (int i = 0; i < 8; ++i) {
            assert(vec[static_cast<unsigned int>(i)] == (i + (i >= 2) * 2));
        }
    }
    {
        ft::vector<std::string> vec(200, "Hello There!");
        assert(vec.size() == 200);
        const std::size_t cap = vec.capacity();
        ft::vector<std::string>::const_iterator it =
            vec.erase(vec.begin() + 50, vec.begin() + 150);
        assert(it == vec.begin() + 50);
        assert(vec.size() == 100);
        assert(vec.capacity() == cap);

        ft::vector<std::string>::iterator tmp = vec.begin();
        for (; tmp != vec.end(); ++tmp) {
            assert(*tmp == "Hello There!");
        }
    }
    {
        ft::vector<test::tracking_class> vec(200);
        std::size_t count = test::tracking_class::instances();
        vec.erase(vec.begin() + 50, vec.begin() + 150);
        assert(test::tracking_class::instances() == count - 100);
    }
    return 0;
}
