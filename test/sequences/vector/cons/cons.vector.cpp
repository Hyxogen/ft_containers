#include <allocators.hpp>
#include <cassert>
#include <classes.hpp>
#include <vector.hpp>

int main() {

    {
        ft::vector<int> vec;
        vec.push_back(5);
        vec.push_back(21);
        vec.push_back(42);
        vec.push_back(34123);
        ft::vector<int> cpy(vec);

        ft::vector<int>::iterator vecit = vec.begin(), cpyit = cpy.begin();
        for (; vecit != vec.end(); ++vecit, ++cpyit) {
            assert(*vecit == *cpyit);
            assert(vecit != cpyit);
        }
    }
    {
        // FIXME: int below here should be test::throwing_class<int>
        ft::vector<test::throwing_class<int>,
                   test::allocator_tracker<test::throwing_class<int> > >
            vec;
        vec.push_back(test::throwing_class<int>(5));
        vec.push_back(test::throwing_class<int>(21));
        vec.push_back(test::throwing_class<int>(42));
        vec.push_back(test::throwing_class<int>(5451341));
        std::size_t used =
            test::allocator_tracker<test::throwing_class<int> >::active();
        test::throwing_class<int>::make_next_throw();
        try {
            // FIXME: int below should be test::throwing_class<int>
            ft::vector<test::throwing_class<int>,
                       test::allocator_tracker<test::throwing_class<int> > >
                cpy(vec);
            assert(false);
        } catch (const test::too_many_instantiations &ex) {
            assert(
                test::allocator_tracker<test::throwing_class<int> >::active() ==
                used);
        }
        test::throwing_class<int>::reset();
    }
    return 0;
}
