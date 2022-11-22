// custom implementation of stl map

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
#ifndef MAP_HPP
#define MAP_HPP

#include <__tree/red_black_tree.hpp>
#include <memory>
#include <functional>
#include <utility.hpp>

namespace ft {

template <class Key, class Value, class Compare = std::less<Key>,
          class Allocator = std::allocator<ft::pair<const Key, Value> > >
class map : detail::rbtree<Key, ft::pair<const Key, Value>, Compare,
                           typename Allocator::template rebind<detail::rbnode<
                               ft::pair<const Key, Value> > >::other> {
        typedef detail::rbtree<
            Key, ft::pair<const Key, Value>, Compare,
            typename Allocator::template rebind<
                detail::rbnode<ft::pair<const Key, Value> > >::other>
            _base;

      public:
        typedef typename _base::value_type value_type;
        typedef typename _base::iterator iterator;

        map() : _base() {}

        explicit map(const Compare &comp, const Allocator &alloc = Allocator())
            : _base(comp, alloc) {}
        

        // TODO write benchmark for this function
        ft::pair<iterator, bool> insert(const value_type &value) {
                return _base::insert(value);
        }
};
}

#endif /* MAP_HPP */
