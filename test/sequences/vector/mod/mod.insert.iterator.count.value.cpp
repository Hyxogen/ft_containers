#include <allocators.hpp>
#include <assert.hpp>
#include <cassert>
#include <classes.hpp>
#include <new>
#include <test.hpp>

int main() {
    {
        ft::vector<int> vec;
        vec.insert(vec.begin(), 42, 42);
        assert(vec.size() == 42);
        assert(vec.capacity() == 42);
        for (size_t idx = 0; idx < 42; ++idx) {
            assert(vec[idx] == 42);
        }
    }
    {
        ft::vector<int> vec;
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);
        vec.insert(vec.begin() + 1, 2, 65);
        assert(vec[0] == 1);
        assert(vec[1] == 65);
        assert(vec[2] == 65);
        assert(vec[3] == 2);
        assert(vec[4] == 3);
        assert(vec.size() == 5);
        assert(vec.capacity() >= 5);
    }
    {
        ft::vector<int> vec;
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);
        vec.insert(vec.begin(), 2, 77);
        assert(vec[0] == 77);
        assert(vec[1] == 77);
        assert(vec[2] == 1);
        assert(vec[3] == 2);
        assert(vec[4] == 3);
        assert(vec.size() == 5);
        assert(vec.capacity() >= 5);
    }
    {
        ft::vector<int> vec;
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);
        vec.insert(vec.end(), 2, 84);
        assert(vec[0] == 1);
        assert(vec[1] == 2);
        assert(vec[2] == 3);
        assert(vec[3] == 84);
        assert(vec[4] == 84);
        assert(vec.size() == 5);
        assert(vec.capacity() >= 5);
    }
    {
        ft::vector<int> vec(30, 99);
        vec.insert(vec.begin() + 20, 10, 22);
        for (size_t idx = 0; idx < 20; ++idx) {
            if (idx < 20) {
                assert(vec[idx] == 99);
            } else if (idx < 30) {
                assert(vec[idx] == 22);
            } else {
                assert(vec[idx] == 99);
            }
        }
    }
    {
        ft::vector<std::string> vec;
        vec.reserve(8);
        vec.push_back("Inserts");
        vec.push_back("count");
        vec.push_back("copies");
        vec.push_back("of");
        vec.push_back("the");

        const ft::vector<std::string>::iterator begin = vec.begin();
        vec.insert(vec.begin() + 2, 3, "value_type");
        assert(vec.begin() == begin);
    }
    {
        typedef test::limited_allocator<std::string> allocator;
        ft::vector<std::string, allocator> vec;
        vec.reserve(5);
        vec.push_back("Inserts");
        vec.push_back("count");
        vec.push_back("copies");
        vec.push_back("of");
        vec.push_back("the");
        allocator::set_limit(allocator::active());
        ASSERT_THROW(vec.insert(vec.begin() + 3, 3, "something"),
                     std::bad_alloc);
        assert(vec.capacity() == 5);
        assert(vec.size() == 5);
        assert(vec[0] == "Inserts");
        assert(vec[1] == "count");
        assert(vec[2] == "copies");
        assert(vec[3] == "of");
        assert(vec[4] == "the");
        allocator::reset_limit();
    }
    {
        typedef test::throwing_class<test::tracking_class> clazz;
        const std::size_t count = test::tracking_class::instances();
        {
            ft::vector<clazz> vec(30);
            clazz::throw_after(5);
            ASSERT_THROW(vec.insert(vec.begin() + 10, 10, clazz()),
                         test::too_many_instantiations);
        }
        assert(test::tracking_class::instances() == count);
        clazz::reset();
    }
    {
        typedef test::throwing_class<test::tracking_class> clazz;
        const std::size_t count = test::tracking_class::instances();
        {
            ft::vector<clazz> vec(30);
            clazz::throw_after(11);
            ASSERT_THROW(vec.insert(vec.begin() + 10, 10, clazz()),
                         test::too_many_instantiations);
        }
        assert(test::tracking_class::instances() == count);
        clazz::reset();
    }
    {
        typedef test::throwing_class<test::tracking_class> clazz;
        const std::size_t count = test::tracking_class::instances();
        {
            ft::vector<clazz> vec(30);
            clazz::throw_after(21);
            ASSERT_THROW(vec.insert(vec.begin() + 10, 10, clazz()),
                         test::too_many_instantiations);
        }
        assert(test::tracking_class::instances() == count);
        clazz::reset();
    }
    {
        typedef test::throwing_class<test::tracking_class> clazz;
        const std::size_t count = test::tracking_class::instances();
        {
            ft::vector<clazz> vec(30);
            clazz::throw_after(3);
            ASSERT_THROW(vec.insert(vec.begin() + 24, 10, clazz()),
                         test::too_many_instantiations);
        }
        assert(test::tracking_class::instances() == count);
        clazz::reset();
    }
    {
        typedef test::throwing_class<test::tracking_class> clazz;
        const std::size_t count = test::tracking_class::instances();
        {
            ft::vector<clazz> vec(30);
            clazz::throw_after(7);
            ASSERT_THROW(vec.insert(vec.begin() + 24, 10, clazz()),
                         test::too_many_instantiations);
        }
        assert(test::tracking_class::instances() == count);
        clazz::reset();
    }
    {
        typedef test::throwing_class<test::tracking_class> clazz;
        const std::size_t count = test::tracking_class::instances();
        {
            ft::vector<clazz> vec(30);
            clazz::throw_after(15);
            ASSERT_THROW(vec.insert(vec.begin() + 24, 10, clazz()),
                         test::too_many_instantiations);
        }
        assert(test::tracking_class::instances() == count);
        clazz::reset();
    }
    return 0;
}
