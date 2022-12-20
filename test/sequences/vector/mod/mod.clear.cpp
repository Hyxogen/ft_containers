#include <cassert>
#include <classes.hpp>
#include <vector.hpp>

int main() {
        {
                ft::vector<int> vec(500, 500);
                ft::vector<int>::size_type capacity = vec.capacity();
                assert(vec.size() == 500);
                vec.clear();
                assert(vec.size() == 0);
                assert(vec.capacity() == capacity);
        }
        {
                std::size_t instances = test::tracking_class::instances();
                ft::vector<test::tracking_class> vec(42);
                assert(test::tracking_class::instances() == instances + 42);
                vec.clear();
                assert(test::tracking_class::instances() == instances);
        }
        return 0;
}
