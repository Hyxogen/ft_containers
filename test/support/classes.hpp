// utility classes used for testing

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
#ifndef CLASSES_HPP
#define CLASSES_HPP

#include <stdexcept>
#include <string>

namespace test {

struct too_many_instantiations : public std::logic_error {
        too_many_instantiations(const std::string &what) : logic_error(what) {}
};

template <typename T> class throwing_class {
        static bool _next_throws;

        T _data;

      public:
        throwing_class() { check(); }

        throwing_class(const T &data) : _data(data) { check(); }

        throwing_class(const throwing_class &other) : _data(other._data) {
                check();
        };

        ~throwing_class() {}

        static void reset() { _next_throws = false; }

        static void make_next_throw() { _next_throws = true; }

        throwing_class &operator=(const throwing_class &other) {
                if (this != &other) {
                        _data = other._data;
                        check();
                }
                return *this;
        }

        bool operator==(const T &data) const { return _data == data; }

        bool operator!=(const T &data) const { return !(_data == data); }

      private:
        static void check() {
                if (_next_throws) {
                        throw too_many_instantiations(
                            "too many instantions of type");
                }
        }
};

template <typename T> bool throwing_class<T>::_next_throws = false;

class tracking_class {
        static std::size_t _instances;

      public:
        tracking_class() { _instances += 1; }

        tracking_class(const tracking_class &other) { _instances += 1; }

        ~tracking_class() { _instances -= 1; }

        static std::size_t instances() { return _instances; }

        tracking_class &operator=(const tracking_class &other) {
                if (this != &other) {
                        _instances -= 1;
                }
                return *this;
        }
};

std::size_t tracking_class::_instances = 0;
}

#endif /* CLASSES_HPP */
