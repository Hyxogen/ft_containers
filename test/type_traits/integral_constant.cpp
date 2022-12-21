#ifndef FT_TEST_STD
#include <test.hpp>
#include <cassert>
#include <type_traits.hpp>
#include <typeinfo>

int main() {
    {
        typedef ft::integral_constant<int, 5> integral;
        integral v;
        assert(typeid(integral::value_type) == typeid(int));
        assert(typeid(integral::type) == typeid(integral));
        assert(integral::value == 5);
        assert(static_cast<int>(v) == 5);
    }
    {
        typedef ft::integral_constant<char, 42> integral;
        integral v;
        assert(typeid(integral::value_type) == typeid(char));
        assert(typeid(integral::type) == typeid(integral));
        assert(integral::value == 42);
        assert(static_cast<char>(v));
    }
    {
        ft::true_type t;
        assert(typeid(ft::true_type::value_type) == typeid(bool));
        assert(typeid(ft::true_type::type) ==
               typeid(ft::integral_constant<bool, true>));
        assert(ft::true_type::value);
        assert(static_cast<bool>(t));
    }
    {
        ft::false_type f;
        assert(typeid(ft::false_type::value_type) == typeid(bool));
        assert(typeid(ft::false_type::type) ==
               typeid(ft::integral_constant<bool, false>));
        assert(!ft::false_type::value);
        assert(!static_cast<bool>(f));
    }
    return 0;
}
#else
int main() {
    return 0;
}
#endif
