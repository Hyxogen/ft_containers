// custom stl utility implementation

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
#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <ostream> //TODO remove

namespace ft {

template <class T1, class T2> struct pair {
        typedef T1 first_type;
        typedef T2 second_type;

        T1 first;
        T2 second;

        pair() : first(), second() {}

        pair(const T1 &x, const T2 &y) : first(x), second(y) {}

        template <class U, class V>
        pair(const pair<U, V> &p) : first(p.first), second(p.second) {}
};

template <class T1, class T2>
bool operator==(const pair<T1, T2> &x, const pair<T1, T2> &y) {
        return x.first == y.first && x.second == y.second;
}

template <class T1, class T2>
bool operator<(const pair<T1, T2> &x, const pair<T1, T2> &y) {
        return x.first < y.first
               || (!(y.first < x.first) && x.second < y.second);
}

template <class T1, class T2>
bool operator>(const pair<T1, T2> &x, const pair<T1, T2> &y) {
	return x < y;
}

template <class T1, class T2>
bool operator<=(const pair<T1, T2> &x, const pair<T1, T2> &y) {
	return !(x > y);
}

template <class T1, class T2>
bool operator>=(const pair<T1, T2> &x, const pair<T1, T2> &y) {
	return !(x < y);
}

template <class T1, class T2>
pair<T1, T2> make_pair(const T1 &x, const T2 &y) {
        return pair<T1, T2>(x, y);
}

// TODO debug code, remove
template <class T1, class T2>
std::ostream &operator<<(std::ostream &stream, const pair<T1, T2> &x) {
        return stream << "(" << x.first << ", " << x.second << ")";
}

}

#endif
