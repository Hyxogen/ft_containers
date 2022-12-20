#ifndef REMOVE_CONST_HPP
#define REMOVE_CONST_HPP

namespace ft {
template <typename T> struct remove_const { typedef T type; };

template <typename T> struct remove_const<const T> { typedef T type; };
} // namespace ft

#endif /* REMOVE_CONST_HPP */
