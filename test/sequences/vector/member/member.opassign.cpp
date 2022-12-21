#include <test.hpp>
#include <allocators.hpp>
#include <cassert>
#include <classes.hpp>

int main() {
    {
        ft::vector<int> *tmp = new ft::vector<int>();
        tmp->push_back(1);
        tmp->push_back(4);
        tmp->push_back(11);
        tmp->push_back(412);
        ft::vector<int> vec;
        vec = *tmp;
        delete tmp;
        assert(vec[0] == 1);
        assert(vec[1] == 4);
        assert(vec[2] == 11);
        assert(vec[3] == 412);
    }
#ifndef FT_TEST_STD
    {
        ft::vector<int, test::limited_allocator<int> > tmp;
        tmp.push_back(43);
        tmp.push_back(51);
        tmp.push_back(82);
        tmp.push_back(101);
        tmp.push_back(520);
        ft::vector<int, test::limited_allocator<int> > vec;
        vec.push_back(3);
        vec.push_back(6);
        vec.push_back(11);
        vec.push_back(13);
        vec.push_back(21);
        vec.push_back(43);
        test::limited_allocator<int>::set_limit(0);
        try {
            vec = tmp;
            assert(false);
        } catch (const std::bad_alloc &ex) {
            assert(vec[0] == 3);
            assert(vec[1] == 6);
            assert(vec[2] == 11);
            assert(vec[3] == 13);
            assert(vec[4] == 21);
            assert(vec[5] == 43);
        }
        test::limited_allocator<int>::set_limit(
            std::numeric_limits<
                test::limited_allocator<int>::size_type>::max());
        vec.push_back(64);
        assert(vec[6] == 64);
    }
    {
        ft::vector<test::throwing_class<int> > tmp(5, test::throwing_class<int>(231));
        ft::vector<test::throwing_class<int> > vec(81, test::throwing_class<int>(54));
        test::throwing_class<int>::make_next_throw();
        try {
            vec = tmp;
            assert(false);
        } catch (const test::too_many_instantiations &ex) {
            test::throwing_class<int>::reset();
            for (std::size_t idx = 0; idx < 81; ++idx) {
                assert(vec[idx] == test::throwing_class<int>(54));
            }
        }
        vec.push_back(test::throwing_class<int>(42));
        assert(vec[81] == 42);
    }
#endif
    return 0;
}
