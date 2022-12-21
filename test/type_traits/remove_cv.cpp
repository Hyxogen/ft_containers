#ifndef FT_TEST_STD
#include <test.hpp>
#include <cassert>
#include <type_traits.hpp>

namespace {
template <typename A, typename B> struct is_same : ft::false_type {};

template <typename A> struct is_same<A, A> : ft::true_type {};

template <typename A, typename B> bool test() { return is_same<A, B>::value; }
} // namespace

int main() {
    assert((test<int, int>()));
    assert((!test<const volatile int, int>()));

    assert((test<ft::remove_cv<volatile int>::type, int>()));
    assert((test<ft::remove_cv<const int>::type, int>()));
    assert((test<ft::remove_cv<const volatile int>::type, int>()));
    assert((test<ft::remove_cv<volatile const int>::type, int>()));
    assert(
        (test<ft::remove_cv<volatile int *volatile>::type, volatile int *>()));
    assert((test<ft::remove_cv<volatile const int *volatile>::type,
                 volatile const int *>()));
    assert((test<ft::remove_cv<volatile const int *const volatile>::type,
                 volatile const int *>()));
    return 0;
}
#else
int main() {
    return 0;
}
#endif
