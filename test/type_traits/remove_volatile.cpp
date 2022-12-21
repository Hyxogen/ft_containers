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
    assert((!test<volatile int, int>()));

    assert((test<ft::remove_volatile<volatile int>::type, int>()));
    assert((test<ft::remove_volatile<const volatile int>::type, const int>()));
    assert((test<ft::remove_volatile<volatile const int>::type, const int>()));
    assert((test<ft::remove_volatile<volatile int *volatile>::type,
                 volatile int *>()));
    assert((test<ft::remove_volatile<volatile const int *volatile>::type,
                 volatile const int *>()));
    return 0;
}
#else
int main() {
    return 0;
}
#endif
