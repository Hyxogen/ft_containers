#include <algorithm.hpp>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <functional>
#include <vector>

template <typename T, typename U> void test(const T &t, const U &u) {
    {
        const bool correct = std::lexicographical_compare(t.begin(), t.end(),
                                                          u.begin(), u.end());
        const bool test =
            ft::lexicographical_compare(t.begin(), t.end(), u.begin(), u.end());
        assert(correct == test);
    }
    {
        const bool correct = std::lexicographical_compare(u.begin(), u.end(),
                                                          t.begin(), t.end());
        const bool test =
            ft::lexicographical_compare(u.begin(), u.end(), t.begin(), t.end());
        assert(correct == test);
    }
}

int main() {
    {
        const std::vector<int> vec;
        test(vec, vec);
    }
    {
        const std::vector<int> vec(300, 42);
        test(vec, vec);
    }
    {
        std::vector<int> vec(300);

        std::generate(vec.begin(), vec.end(), std::rand);
        test(vec, vec);
    }
    {
        const std::vector<int> vec1(300, 42);
        const std::vector<int> vec2(vec1);
        test(vec1, vec2);
    }
    {
        const std::vector<int> vec1(300, 42);
        const std::vector<int> vec2(301, 42);
        test(vec1, vec2);
    }
    {
        std::vector<int> vec1(300);
        std::generate(vec1.begin(), vec1.end(), std::rand);
        std::vector<int> vec2(vec1);
        if (vec2[99] > 500) {
            vec2[99] -= 1;
        } else {
            vec2[99] += 1;
        }
        test(vec1, vec2);
    }
    return 0;
}
