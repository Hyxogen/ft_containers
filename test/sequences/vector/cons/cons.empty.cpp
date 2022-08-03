// default empty constructor vector test

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
#include <vector.hpp>
#include <allocators.hpp>
#include <cassert>
#include <typeinfo>
#include <memory>

int main() {
	{
		ft::vector<int> vec;
		assert(vec.empty());
	}
	assert(typeid(ft::vector<int>::allocator_type) == typeid(std::allocator<int>));
	assert(typeid(ft::vector<int, test::allocator_wrapper<int> >::allocator_type) == typeid(test::allocator_wrapper<int>));
	return 0;
}
