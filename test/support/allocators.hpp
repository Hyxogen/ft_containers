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
#include <limits>
#include <map>
#include <memory>
#include <new>
#include <string>
#include <cstdlib>

namespace test {
namespace {
std::map<std::string, std::size_t> calls;
}

template <typename It, typename T>
struct stateful_allocator {
        It t;
        typedef T value_type;
        typedef value_type *pointer;
	typedef const value_type *const_pointer;
	typedef value_type &reference;
	typedef const value_type &const_reference;
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;

        template <class U> struct rebind {
                typedef stateful_allocator<It, U> other;
        };

	stateful_allocator(const It &t) : t(t) {}

        template <class U>
        stateful_allocator(const stateful_allocator<It, U> &other)
            : t(other.t) {
        }

        pointer address(reference x) const {
		return std::allocator<value_type>().address(x);
        }

        const_pointer address(const_reference x) const {
		return std::allocator<value_type>().address(x);
        }

        pointer allocate(size_type n, const void *hint = 0) {
		return std::allocator<value_type>().allocate(n, hint);
        }

        void deallocate(T *p, std::size_t n) {
		return std::allocator<value_type>().deallocate(p, n);
        }

        size_type max_size() const throw() {
		return std::allocator<value_type>().max_size();
        }

        void construct(pointer p, const_reference val) {
		return std::allocator<value_type>().construct(p, val);
        }

        void destroy(pointer p) {
		return std::allocator<value_type>().destroy(p);
        }

        bool operator==(const stateful_allocator &other) const {
		return t == other.t;
	}
};

template <typename T, typename Base = std::allocator<T> >
struct allocator_wrapper : Base {
        typedef typename Base::value_type value_type;
        typedef typename Base::pointer pointer;
        typedef typename Base::const_pointer const_pointer;
        typedef typename Base::reference reference;
        typedef typename Base::const_reference const_reference;
        typedef typename Base::size_type size_type;
        typedef typename Base::difference_type difference_type;

        allocator_wrapper() : Base() { call("default"); }

        allocator_wrapper(const allocator_wrapper &other) : Base(other) {
                call("copy");
        }

        template <class U>
        allocator_wrapper(const allocator_wrapper<U, Base> &other)
            : Base(other) {
                call("copy_other");
        }

        pointer address(reference x) const {
                call("address");
                return Base::address(x);
        }

        const_pointer address(const_reference x) const {
                call("const_address");
                return Base::address(x);
        }

        pointer allocate(size_type n, const void *hint = 0) {
                call("allocate");
                return Base::allocate(n, hint);
        }

        void deallocate(T *p, std::size_t n) {
                call("deallocate");
                return Base::deallocate(p, n);
        }

        size_type max_size() const throw() {
                call("max_size");
                return Base::max_size();
        }

        void construct(pointer p, const_reference val) {
                call("construct");
                return Base::construct(p, val);
        }

        void destroy(pointer p) {
                call("destroy");
                return Base::destroy(p);
        }

      private:
        static void call(const std::string &name) { calls[name] += 1; }
};
template <typename T, typename Base = std::allocator<T> >
struct allocator_tracker : Base {
        typedef typename Base::size_type size_type;
        template <class U> struct rebind {
                typedef allocator_tracker<U> other;
        };

      private:
        static size_type _active;
        static std::size_t _alloc_count;

      public:
        static size_type active() { return _active; }
        static std::size_t alloc_count() { return _alloc_count; }

        typename Base::pointer allocate(size_type n, const void *hint = 0) {
                _active += n;
                _alloc_count += 1;
                return Base::allocate(n, hint);
        }

        void deallocate(T *p, std::size_t n) {
                _active -= n;
                return Base::deallocate(p, n);
        }
};

template <typename T> struct limited_allocator : allocator_tracker<T> {
        typedef allocator_tracker<T> _base;
        typedef typename _base::size_type size_type;
        template <class U> struct rebind {
                typedef limited_allocator<U> other;
        };

      private:
        static size_type _limit;

      public:
        static void set_limit(size_type limit) { _limit = limit; }

        static void reset_limit() {
                _limit = std::numeric_limits<
                    typename limited_allocator<T>::size_type>::max();
        }

        typename _base::pointer allocate(size_type n, const void *hint = 0) {
                if (_base::active() + n >= _limit) {
                        throw std::bad_alloc();
                }
                return _base::allocate(n, hint);
        }

        void deallocate(T *p, std::size_t n) {
                return _base::deallocate(p, n);
        }
};

template <typename T, typename Base>
typename Base::size_type allocator_tracker<T, Base>::_active = 0;

template <typename T, typename Base>
std::size_t allocator_tracker<T, Base>::_alloc_count = 0;

template <typename T>
typename limited_allocator<T>::size_type limited_allocator<T>::_limit
    = std::numeric_limits<typename limited_allocator<T>::size_type>::max();

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
