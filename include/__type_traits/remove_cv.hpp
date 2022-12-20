#ifndef REMOVE_CV_HPP
#define REMOVE_CV_HPP

#include <__type_traits/remove_const.hpp>
#include <__type_traits/remove_volatile.hpp>

namespace ft {
template <class T> struct remove_cv {
    typedef
        typename ft::remove_const<typename ft::remove_volatile<T>::type>::type
            type;
};
} // namespace ft

#endif /* REMOVE_CV_HPP */
