#ifndef FT_TEST_STD
#include <test.hpp>
#include <cassert>
#include <type_traits.hpp>

static ft::enable_if<true, void>::type test() {}

int main() {
    test();
    return 0;
}
#else
int main() {
    return 0;
}
#endif
