#include <cassert>
#include <classes.hpp>
#include <vector.hpp>

int main() {
        {
                ft::vector<int> vec;
                vec.assign(3, 42);
                assert(vec.size() == 3);
                assert(vec.capacity() >= 3);
                assert(vec[0] == 42);
                assert(vec[1] == 42);
                assert(vec[2] == 42);
        }
        {
                std::size_t instances = test::tracking_class::instances();
                ft::vector<test::tracking_class> vec(100);
                vec.assign(3, test::tracking_class());
                assert(test::tracking_class::instances() == instances + 3);
        }
        return 0;
}
