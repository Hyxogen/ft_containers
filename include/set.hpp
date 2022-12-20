#ifndef SET_HPP
#define SET_HPP

#include <__tree/red_black_tree.hpp>
#include <cstddef>
#include <functional>
#include <memory>

namespace ft {

template <class Key, class Compare = std::less<Key>,
          class Allocator = std::allocator<Key>>
class set
    : public detail::rbtree<
          Key, Key, detail::use_self<Key>, Compare,
          typename Allocator::template rebind<detail::rbnode<Key>>::other> {

    typedef detail::rbtree<
        Key, Key, detail::use_self<Key>, Compare,
        typename Allocator::template rebind<detail::rbnode<Key>>::other>
        _base;

  public:
    using typename _base::key_type;
    using typename _base::size_type;
    using typename _base::value_type;
    typedef std::ptrdiff_t difference_type;
    using typename _base::key_compare;
    typedef key_compare value_compare;
    typedef value_type &reference;
    typedef const value_type &const_reference;
    typedef Allocator allocator_type;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    using typename _base::const_iterator;
    using typename _base::const_reverse_iterator;
    using typename _base::iterator;
    using typename _base::reverse_iterator;

    set() : _base() {}

    explicit set(const Compare &comp, const Allocator &alloc = Allocator())
        : _base(comp, alloc) {}

    template <class InputIt>
    set(InputIt first, InputIt last, const Compare &comp = Compare(),
        const Allocator &alloc = Allocator())
        : _base(first, last, comp, alloc) {}

    set(const set &other) : _base(other) {}

    allocator_type get_allocator() const { return _base::get_allocator(); }

    using _base::begin;
    using _base::clear;
    using _base::empty;
    using _base::end;
    using _base::insert;
    using _base::max_size;
    using _base::rbegin;
    using _base::rend;
    using _base::size;

    void erase(iterator position) { _base::erase(position); }

    size_type erase(const key_type &x) { return _base::erase(x); }

    void erase(iterator first, iterator last) { _base::erase(first, last); }

    using _base::key_comp;
    using _base::swap;

    value_compare value_comp() const { return key_comp(); }

    using _base::count;
    using _base::find;

    using _base::equal_range;
    using _base::lower_bound;
    using _base::upper_bound;
};
} // namespace ft

#endif /* SET_HPP */
