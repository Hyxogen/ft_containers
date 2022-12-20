#include <allocators.hpp>
#include <assert.hpp>
#include <cassert>
#include <string>
#include <vector.hpp>
#include <stdexcept>

int main() {
        {
                ft::vector<int> vec;
                assert(vec.capacity() == 0);
                vec.reserve(0);
                assert(vec.capacity() == 0);
        }
        {
                ft::vector<int> vec(20);
                std::size_t cap = vec.capacity();
                assert(cap >= 20);
                vec.reserve(10);
                assert(vec.capacity() == cap);
        }
        {
                ft::vector<std::string> vec(1, "Hello There");
                assert(vec.capacity() == 1);
                vec.reserve(100);
                assert(vec.capacity() == 100);
                assert(vec[0] == "Hello There");
        }
        {
                typedef test::limited_allocator<std::string> allocator;
                ft::vector<std::string, allocator> vec(3);
                assert(vec.capacity() == 3);
                vec[0] = "Well";
                vec[1] = "Hello";
                vec[2] = "There";
                allocator::set_limit(allocator::active() + 1);
                ASSERT_THROW(vec.reserve(10), std::bad_alloc);
                assert(vec.capacity() == 3);
                assert(vec[0] == "Well");
                assert(vec[1] == "Hello");
                assert(vec[2] == "There");
        }
        {
                typedef test::limited_allocator<std::string> allocator;
                const std::size_t usage = allocator::active();
                {
                        ft::vector<std::string, allocator> vec(3);
                        assert(vec.capacity() == 3);
                        vec[0] = "Well";
                        vec[1] = "Hello";
                        vec[2] = "There";
                        allocator::set_limit(allocator::active() + 1);
                        ASSERT_THROW(vec.reserve(10), std::bad_alloc);
                        assert(vec.capacity() == 3);
                        assert(vec[0] == "Well");
                        assert(vec[1] == "Hello");
                        assert(vec[2] == "There");
                }
                assert(allocator::active() == usage);
        }
        {
                ft::vector<std::string> vec;
                ASSERT_THROW(vec.reserve(std::numeric_limits<size_t>::max()),
                             std::length_error);
                ASSERT_THROW(
                    vec.reserve(
                        (std::numeric_limits<
                             std::allocator<std::string>::size_type>::max()
                         / sizeof(std::string))
                        + 1),
                    std::length_error);
        }
        return 0;
}
