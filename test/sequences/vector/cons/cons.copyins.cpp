#include <test.hpp>
#include <allocators.hpp>
#include <cassert>
#include <classes.hpp>

int main() {
    {
        ft::vector<int> vec(5, 42);
        assert(vec.size() == 5);
        assert(vec.capacity() >= 5);
        assert(vec[0] == 42);
        assert(vec[1] == 42);
        assert(vec[2] == 42);
        assert(vec[3] == 42);
        assert(vec[4] == 42);
    }
#ifndef FT_TEST_STD
    {
        test::allocator_wrapper<int> alloc;
        std::size_t count = test::calls["copy"];
        ft::vector<int, test::allocator_wrapper<int> > vec(5, 42);
        assert(vec.size() == 5);
        assert(vec.capacity() >= 5);
        assert(vec[0] == 42);
        assert(vec[1] == 42);
        assert(vec[2] == 42);
        assert(vec[3] == 42);
        assert(vec[4] == 42);
        assert((test::calls["copy"] - count) == 1);
    }
#endif
    {
        test::throwing_class<int> clazz;
        std::size_t used =
            test::allocator_tracker<test::throwing_class<int> >::active();
        test::throwing_class<int>::make_next_throw();
        try {
            ft::vector<test::throwing_class<int>,
                       test::allocator_tracker<test::throwing_class<int> > >
                vec(5, clazz);
            assert(false);
        } catch (const test::too_many_instantiations &ex) {
            assert(
                test::allocator_tracker<test::throwing_class<int> >::active() ==
                used);
        }
    }
    {
        std::size_t instances = test::tracking_class::instances();
        { ft::vector<test::tracking_class> vec(42); }
        assert(test::tracking_class::instances() == instances);
    }
    return 0;
}
