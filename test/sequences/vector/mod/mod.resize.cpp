#include <test.hpp>
#include <allocators.hpp>
#include <assert.hpp>
#include <cassert>
#include <classes.hpp>
#include <cstddef>


int main() {
    {
        ft::vector<int> vec;
        vec.resize(0);
        assert(vec.capacity() == 0);
    }
    {
        ft::vector<std::string> vec;
        vec.resize(100, "42");
        ft::vector<std::string>::iterator it = vec.begin();
        for (; it != vec.end(); ++it) {
            assert(*it == "42");
        }
    }
    {
        ft::vector<int> vec(500, 42);
        const std::size_t cap = vec.capacity();
        vec.resize(100);
        assert(vec.capacity() == cap);
        assert(vec.size() == 100);
    }
#ifndef FT_TEST_STD
    {
        ft::vector<int> vec(500, 42);
        vec.resize(600, 42);
        assert(vec.capacity() == 600);
        assert(vec.size() == 600);
        ft::vector<int>::iterator it = vec.begin();
        for (; it != vec.end(); ++it) {
            assert(*it == 42);
        }
    }
#endif
    {
        typedef test::tracking_class clazz;

        const std::size_t active = clazz::instances();
        ft::vector<clazz> vec(200);
        vec.resize(100);
        assert(clazz::instances() == active + 100);
        vec.resize(0);
        assert(clazz::instances() == active);
        assert(vec.size() == 0);
    }
    {
        ft::vector<std::string> vec(100, "<language> rules!");
        vec.resize(200, "<other language> drools!");
        for (std::size_t idx = 0; idx < vec.size(); ++idx) {
            if (idx < 100) {
                assert(vec[idx] == "<language> rules!");
            } else {
                assert(vec[idx] == "<other language> drools!");
            }
        }
    }
    {
        typedef test::limited_allocator<std::string> allocator;
        ft::vector<std::string, allocator> vec;
        vec.push_back("i");
        vec.push_back("used");
        vec.push_back("to");
        vec.push_back("be");
        vec.push_back("an");
        vec.push_back("adventurer");
        vec.push_back("like");
        vec.push_back("you");

        const std::size_t cap = vec.capacity();

        allocator::set_limit(0);
        ASSERT_THROW(vec.resize(cap + 10), std::bad_alloc);

        assert(vec.capacity() == cap);
        assert(vec.size() == 8);
        assert(vec[0] == "i");
        assert(vec[1] == "used");
        assert(vec[2] == "to");
        assert(vec[3] == "be");
        assert(vec[4] == "an");
        assert(vec[5] == "adventurer");
        assert(vec[6] == "like");
        assert(vec[7] == "you");
    }
    {
        typedef test::throwing_class<std::string> clazz;
        ft::vector<clazz> vec(10, clazz("foo"));

        clazz::make_next_throw();
        std::size_t cap = vec.capacity();
        ASSERT_THROW(vec.resize(3), test::too_many_instantiations);

        assert(vec.capacity() == cap);
        assert(vec.size() == 10);
        ft::vector<clazz>::iterator it = vec.begin(), end = vec.end();
        for (; it != end; ++it) {
            assert(*it == "foo");
        }

        clazz::reset();
        vec.push_back(clazz("middle"));

        cap = vec.capacity();
        clazz::make_next_throw();
        ASSERT_THROW(vec.resize(100, clazz("bar")),
                     test::too_many_instantiations);
        it = vec.begin();
        end = vec.end();

        for (; it != end - 1; ++it) {
            assert(*it == "foo");
        }
        assert(*it++ == "middle");
        assert(it == vec.end());
    }
    return 0;
}
