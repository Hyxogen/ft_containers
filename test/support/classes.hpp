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

template <int ThrowAfter> class throwing_class {
        static int _left;

      public:
        throwing_class() { check_and_decrease_counter(); }

        throwing_class(const throwing_class &other) {
                (void)other;
                check_and_decrease_counter();
        };

        ~throwing_class() {}

        static void reset_counter() { _left = ThrowAfter; }

        throwing_class &operator=(const throwing_class &other) {
                if (this != &other) {
                        check_and_decrease_counter();
                }
                return *this;
        }

      private:
        static void check_and_decrease_counter() {
                if (_left == 0) {
                        throw too_many_instantiations(
                            "too many instantions of type");
                }
                --_left;
        }
};

template <int ThrowAfter> int throwing_class<ThrowAfter>::_left = ThrowAfter;
}

#endif /* CLASSES_HPP */
