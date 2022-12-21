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
    assert((!test<const int, int>()));

    assert((test<ft::remove_const<const int>::type, int>()));
    assert((test<ft::remove_const<const volatile int>::type, volatile int>()));
    assert((test<ft::remove_const<volatile const int>::type, volatile int>()));
    assert((test<ft::remove_const<const int *const>::type, const int *>()));
    return 0;
}
#else
int main() {
    return 0;
}
#endif
