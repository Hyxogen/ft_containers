#ifndef MAP_HPP
#define MAP_HPP

#include <__tree/red_black_tree.hpp>
#include <cstddef>
#include <functional>
#include <memory>
#include <stdexcept>
#include <utility.hpp>

namespace ft {

template <class Key, class T, class Compare = std::less<Key>,
          class Allocator = std::allocator<ft::pair<const Key, T>>>
class map
    : public detail::rbtree<Key, ft::pair<const Key, T>,
                            detail::use_first<ft::pair<const Key, T>>, Compare,
                            typename Allocator::template rebind<detail::rbnode<
                                ft::pair<const Key, T>>>::other> {
    typedef detail::rbtree<Key, ft::pair<const Key, T>,
                           detail::use_first<ft::pair<const Key, T>>, Compare,
                           typename Allocator::template rebind<
                               detail::rbnode<ft::pair<const Key, T>>>::other>
        _base;

  public:
    typedef typename _base::key_type key_type;
    typedef T mapped_type;
    typedef typename _base::value_type value_type;
    typedef typename _base::size_type size_type;
    typedef std::ptrdiff_t difference_type;
    typedef typename _base::key_compare key_compare;
    typedef value_type &reference;
    typedef const value_type &const_reference;
    typedef Allocator allocator_type;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    typedef typename _base::iterator iterator;
    typedef typename _base::const_iterator const_iterator;
    typedef typename _base::reverse_iterator reverse_iterator;
    typedef typename _base::const_reverse_iterator const_reverse_iterator;

    class value_compare
        : public std::binary_function<value_type, value_type, bool> {
        friend class map;

      protected:
        Compare comp;
        value_compare(Compare c) : comp(c) {}

      public:
        bool operator()(const value_type &lhs, const value_type &rhs) const {
            return comp(lhs.first, rhs.first);
        }
    };

    map() : _base() {}

    explicit map(const Compare &comp, const Allocator &alloc = Allocator())
        : _base(comp, alloc) {}

    template <class InputIt>
    map(InputIt first, InputIt last, const Compare &comp = Compare(),
        const Allocator &alloc = Allocator())
        : _base(first, last, comp, alloc) {}

    map(const map &other) : _base(other) {}

    allocator_type get_allocator() const { return _base::get_allocator(); }

    using _base::begin;
    using _base::empty;
    using _base::end;
    using _base::max_size;
    using _base::rbegin;
    using _base::rend;
    using _base::size;

    // TODO add test for this function
    const T &at(const key_type &x) const {
        const const_iterator pos = find(x);
        if (pos == end()) {
            throw std::out_of_range("out of range in map::at");
        }
        return pos->second;
    }

    T &at(const key_type &x) {
        return const_cast<T &>(static_cast<const map *>(this)->at(x));
    }

    T &operator[](const key_type &x) {
        return (*((insert(ft::make_pair(x, T()))).first)).second;
    }

    using _base::insert;

    void erase(iterator position) { _base::erase(position); }

    size_type erase(const key_type &x) { return _base::erase(x); }

    void erase(iterator first, iterator last) { _base::erase(first, last); }

    using _base::clear;
    using _base::swap;

    using _base::key_comp;

    value_compare value_comp() const { return value_compare(key_comp()); }

    using _base::count;
    using _base::find;

    using _base::equal_range;
    using _base::lower_bound;
    using _base::upper_bound;
};
} // namespace ft

#endif /* MAP_HPP */
