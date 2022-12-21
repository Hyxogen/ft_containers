#include <test.hpp>
#include <allocators.hpp>
#include <cassert>
#include <memory>
#include <typeinfo>

int main() {
    {
        ft::vector<int> vec;
        assert(vec.empty());
    }
    assert(typeid(ft::vector<int>::allocator_type) ==
           typeid(std::allocator<int>));
    assert(
        typeid(
            ft::vector<int, test::allocator_wrapper<int> >::allocator_type) ==
        typeid(test::allocator_wrapper<int>));
    return 0;
}
