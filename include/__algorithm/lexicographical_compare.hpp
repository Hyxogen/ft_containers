// custom lexicographical_compare implementation

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
#ifndef LEXICOGRAPHICAL_COMPARE_HPP
#define LEXICOGRAPHICAL_COMPARE_HPP

namespace ft {

template <class InputIt1, class InputIt2>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                             InputIt2 last2) {
        for (; (first1 != last1) && (first2 != last2);
             ++first1, (void)++first2) {
                if (*first1 < *first2) {
                        return true;
                }
                if (*first2 < *first1) {
                        return false;
                }
        }
        return (first1 == last1) && (first2 != last2);
}

template <class InputIt1, class InputIt2, class Compare>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                             InputIt2 last2, Compare comp) {
        for (; (first1 != last1) && (first2 != last2);
             ++first1, (void)++first2) {
                if (comp(*first1, *first2)) {
                        return true;
                }
                if (comp(*first2, *first1)) {
                        return false;
                }
        }
        return (first1 == last1) && (first2 != last2);
}
}

#endif /* LEXICOGRAPHICAL_COMPARE_HPP */
