#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP

namespace ft {
template <bool B, class T> struct enable_if;

template <class T> struct enable_if<true, T> { typedef T type; };
} // namespace ft

#endif /* ENABLE_IF_HPP */
