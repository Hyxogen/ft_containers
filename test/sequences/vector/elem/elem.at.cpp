#include <test.hpp>
#include <assert.hpp>
#include <stdexcept>

int main() {
    {
        ft::vector<int> vec;
        ASSERT_THROW(vec.at(0), std::out_of_range);
    }
    {
        const ft::vector<int> vec;
        ASSERT_THROW(vec.at(0), std::out_of_range);
    }
    {
        ft::vector<int> vec(300, 42);
        for (unsigned int idx = 0; idx < 300; ++idx) {
            assert(vec.at(idx) == 42);
            ASSERT_THROW(vec.at(300 + idx), std::out_of_range);
        }
    }
    {
        const ft::vector<int> vec(300, 42);
        for (unsigned int idx = 0; idx < 300; ++idx) {
            assert(vec.at(idx) == 42);
            ASSERT_THROW(vec.at(300 + idx), std::out_of_range);
        }
    }
    {
        ft::vector<int> vec;
        for (int idx = 0; idx < 300; ++idx) {
            vec.push_back(idx);
        }
        for (unsigned int idx = 0; idx < 300; ++idx) {
            assert(vec.at(idx) == static_cast<int>(idx));
        }
    }
    {
        ft::vector<int> vec;
        for (int idx = 0; idx < 300; ++idx) {
            vec.push_back(idx);
        }
        for (unsigned int idx = 0; idx < 300; ++idx) {
            assert(vec.at(idx) == static_cast<int>(idx));
        }
    }
    {
        ft::vector<int> tmp;
        for (int idx = 0; idx < 300; ++idx) {
            tmp.push_back(idx);
        }
        const ft::vector<int> vec(tmp);
        for (unsigned int idx = 0; idx < 300; ++idx) {
            assert(vec.at(idx) == static_cast<int>(idx));
        }
    }
    return 0;
}
