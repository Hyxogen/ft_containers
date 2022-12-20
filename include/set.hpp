// custom stl set implementation

// Copyright (C) 2022 Daan Meijer
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
#ifndef SET_HPP
#define SET_HPP

#include <__tree/red_black_tree.hpp>
#include <functional>
#include <memory>
#include <cstddef>

namespace ft {

template <class Key, class Compare = std::less<Key>,
          class Allocator = std::allocator<Key> >
class set
    : public detail::rbtree<
          Key, Key, detail::use_self<Key>, Compare,
          typename Allocator::template rebind<detail::rbnode<Key> >::other> {

        typedef detail::rbtree<
            Key, Key, detail::use_self<Key>, Compare,
            typename Allocator::template rebind<detail::rbnode<Key> >::other>
            _base;

      public:
	using typename _base::key_type;
        using typename _base::value_type;
	using typename _base::size_type;
	typedef std::ptrdiff_t difference_type;
	using typename _base::key_compare;
	typedef key_compare value_compare;
	typedef value_type &reference;
	typedef const value_type &const_reference;
	typedef Allocator allocator_type;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
        using typename _base::iterator;
        using typename _base::const_iterator;
        using typename _base::reverse_iterator;
        using typename _base::const_reverse_iterator;

        set() : _base() {}

        explicit set(const Compare &comp, const Allocator &alloc = Allocator())
            : _base(comp, alloc) {}

        template <class InputIt>
        set(InputIt first, InputIt last, const Compare &comp = Compare(),
            const Allocator &alloc = Allocator())
            : _base(first, last, comp, alloc) {}

        set(const set &other) : _base(other) {}

	allocator_type get_allocator() const {
		return _base::get_allocator();
	}

        using _base::begin;
        using _base::end;
        using _base::rbegin;
        using _base::rend;
	using _base::empty;
	using _base::size;
	using _base::max_size;
	using _base::clear;
        using _base::insert;

	void erase(iterator position) {
		_base::erase(position);
	}

	size_type erase(const key_type &x) {
		return _base::erase(x);
	}

	void erase(iterator first, iterator last) {
		_base::erase(first, last);
	}

	using _base::swap;
	using _base::key_comp;

	value_compare value_comp() const {
		return key_comp();
	}

	using _base::find;
	using _base::count;

	using _base::lower_bound;
	using _base::upper_bound;
	using _base::equal_range;
};
}

#endif /* SET_HPP */
