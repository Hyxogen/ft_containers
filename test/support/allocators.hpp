// utility allocators used for testing

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
#include <memory>

namespace test {
template <typename T, typename Base = std::allocator<T> >
struct allocator_wrapper : Base {
        typedef typename Base::value_type value_type;
        typedef typename Base::pointer pointer;
        typedef typename Base::const_pointer const_pointer;
        typedef typename Base::reference reference;
        typedef typename Base::const_reference const_reference;
        typedef typename Base::size_type size_type;
        typedef typename Base::difference_type difference_type;

        allocator_wrapper() : Base() {}
        allocator_wrapper(const allocator_wrapper &other) : Base(other) {}
        template <class U>
        allocator_wrapper(const allocator_wrapper<U, Base> &other)
            : Base(other) {}

        pointer address(reference x) const { return Base::address(x); }
        const_pointer address(const_reference x) const {
                return Base::address(x);
        }
        pointer allocate(size_type n, const void *hint = 0) {
                return Base::allocate(n, hint);
        }
        void deallocate(T *p, std::size_t n) { return Base::deallocate(p, n); }
        size_type max_size() const throw() { return Base::max_size(); }
        void construct(pointer p, const_reference val) {
                return Base::construct(p, val);
        }
        void destroy(pointer p) { return Base::destroy(p); }
};
template <class T1, class T2, class Base>
bool operator==(const allocator_wrapper<T1, Base> &lhs,
                const allocator_wrapper<T2, Base> &rhs) throw() {
        return static_cast<Base>(lhs) == static_cast<Base>(rhs);
}
template <class T1, class T2, class Base>
bool operator!=(const allocator_wrapper<T1, Base> &lhs,
                const allocator_wrapper<T2, Base> &rhs) throw() {
        return static_cast<Base>(lhs) != static_cast<Base>(rhs);
}
}
