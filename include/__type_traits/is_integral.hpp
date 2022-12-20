#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

#include <__type_traits/integral_constant.hpp>
#include <__type_traits/remove_cv.hpp>

namespace ft {

namespace detail {
template <class T> struct is_integral : false_type {};

template <> struct is_integral<bool> : true_type {};
template <> struct is_integral<char> : true_type {};
template <> struct is_integral<signed char> : true_type {};
template <> struct is_integral<unsigned char> : true_type {};
template <> struct is_integral<short> : true_type {};
template <> struct is_integral<unsigned short> : true_type {};
template <> struct is_integral<int> : true_type {};
template <> struct is_integral<unsigned int> : true_type {};
template <> struct is_integral<long> : true_type {};
template <> struct is_integral<unsigned long> : true_type {};
} // namespace detail

template <class T>
struct is_integral : detail::is_integral<typename ft::remove_cv<T>::type> {};
} // namespace ft

#endif /* IS_INTEGRAL_HPP */
