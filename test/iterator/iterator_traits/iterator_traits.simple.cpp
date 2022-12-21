#include <cassert>
#include <iterator>
#include <test.hpp>
#include <typeinfo>

template <typename T> void test() {
    assert(typeid(typename ft::iterator_traits<T>::difference_type) ==
           typeid(typename std::iterator_traits<T>::difference_type));
    assert(typeid(typename ft::iterator_traits<T>::value_type) ==
           typeid(typename std::iterator_traits<T>::value_type));
    assert(typeid(typename ft::iterator_traits<T>::pointer) ==
           typeid(typename std::iterator_traits<T>::pointer));
    assert(typeid(typename ft::iterator_traits<T>::reference) ==
           typeid(typename std::iterator_traits<T>::reference));
    assert(typeid(typename ft::iterator_traits<T>::iterator_category) ==
           typeid(typename std::iterator_traits<T>::iterator_category));
}

int main() {
    test<int *>();
    test<const int *>();
}
