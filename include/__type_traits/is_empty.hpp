#ifndef IS_EMPTY
#define IS_EMPTY

#include <__type_traits/integral_constant.hpp>

namespace ft {
namespace detail {

#ifdef FT_USE_ISEMPTY
template <class T>
struct is_empty : public integral_constant<bool, __is_empty(T)> {};
#else
template <class T> struct is_empty : public false_type {};
#endif
}
}

#endif
