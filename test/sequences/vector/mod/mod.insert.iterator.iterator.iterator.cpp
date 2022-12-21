#include <allocators.hpp>
#include <assert.hpp>
#include <cassert>
#include <classes.hpp>
#include <iterator>
#include <iterators.hpp>
#include <new>
#include <sstream>
#include <string>
#include <test.hpp>

int main() {
    {
        ft::vector<int> vec;

        vec.insert(vec.begin(), test::range_iterator<int>(0),
                   test::range_iterator<int>(500));
        assert(vec.size() == 500);
        assert(vec.capacity() >= 500);
        for (size_t idx = 0; idx < 500; ++idx) {
            assert(vec[idx] == static_cast<int>(idx));
        }
    }
    {
        ft::vector<int> vec;

        vec.push_back(0);
        vec.push_back(1);
        vec.push_back(501);
        vec.push_back(502);
        vec.push_back(503);
        vec.push_back(504);
        vec.insert(vec.begin() + 2, test::range_iterator<int>(2),
                   test::range_iterator<int>(501));
        assert(vec.size() == 505);
        assert(vec.capacity() >= 505);
        for (size_t idx = 0; idx < 505; ++idx) {
            assert(vec[idx] == static_cast<int>(idx));
        }
    }
    {
        ft::vector<int> vec;

        vec.push_back(0);
        vec.push_back(1);
        vec.push_back(7);
        vec.push_back(8);
        vec.push_back(9);
        vec.insert(vec.begin() + 2, test::range_iterator<int>(2),
                   test::range_iterator<int>(7));
        assert(vec.size() == 10);
        assert(vec.capacity() >= 10);
        for (size_t idx = 0; idx < 10; ++idx) {
            assert(vec[idx] == static_cast<int>(idx));
        }
    }
    {
        ft::vector<int> vec;

        vec.push_back(500);
        vec.push_back(501);
        vec.push_back(502);
        vec.push_back(503);
        vec.push_back(504);
        vec.insert(vec.begin(), test::range_iterator<int>(0),
                   test::range_iterator<int>(500));
        for (size_t idx = 0; idx < 505; ++idx) {
            assert(vec[idx] == static_cast<int>(idx));
        }
    }
    {
        ft::vector<int> vec;

        vec.push_back(0);
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);
        vec.push_back(4);
        vec.push_back(5);
        vec.insert(vec.end(), test::range_iterator<int>(6),
                   test::range_iterator<int>(500));
        assert(vec.size() == 500);
        assert(vec.capacity() >= 500);
        for (size_t idx = 0; idx < 500; ++idx) {
            assert(vec[idx] == static_cast<int>(idx));
        }
    }
    {
        ft::vector<std::string> vec;

        std::stringstream stream("If they are input iterators, the complexity");
        std::istream_iterator<std::string> str_it(stream);

        vec.insert(vec.begin(), str_it, std::istream_iterator<std::string>());
        assert(vec.size() == 7);
        assert(vec.capacity() >= 7);
        assert(vec[0] == "If");
        assert(vec[1] == "they");
        assert(vec[2] == "are");
        assert(vec[3] == "input");
        assert(vec[4] == "iterators,");
        assert(vec[5] == "the");
        assert(vec[6] == "complexity");
    }
    {
        ft::vector<std::string> vec;

        vec.push_back("Lorem");
        vec.push_back("ipsum");
        vec.push_back("consectetur");
        vec.push_back("adipiscing");
        vec.push_back("elit,");
        vec.push_back("sed");

        std::stringstream stream("dolor sit amet,");
        std::istream_iterator<std::string> str_it(stream);
        vec.insert(vec.begin() + 2, str_it,
                   std::istream_iterator<std::string>());
        assert(vec.size() == 9);
        assert(vec.capacity() >= 9);
        assert(vec[0] == "Lorem");
        assert(vec[1] == "ipsum");
        assert(vec[2] == "dolor");
        assert(vec[3] == "sit");
        assert(vec[4] == "amet,");
        assert(vec[5] == "consectetur");
        assert(vec[6] == "adipiscing");
        assert(vec[7] == "elit,");
        assert(vec[8] == "sed");
    }
    {
        ft::vector<std::string> vec;

        vec.push_back("Lorem");
        vec.push_back("ipsum");
        vec.push_back("dolor");
        vec.push_back("sit");
        vec.push_back("elit,");
        vec.push_back("sed");

        std::stringstream stream("amet, consectetur adipiscing");
        std::istream_iterator<std::string> str_it(stream);
        vec.insert(vec.begin() + 4, str_it,
                   std::istream_iterator<std::string>());
        assert(vec.size() == 9);
        assert(vec.capacity() >= 9);
        assert(vec[0] == "Lorem");
        assert(vec[1] == "ipsum");
        assert(vec[2] == "dolor");
        assert(vec[3] == "sit");
        assert(vec[4] == "amet,");
        assert(vec[5] == "consectetur");
        assert(vec[6] == "adipiscing");
        assert(vec[7] == "elit,");
        assert(vec[8] == "sed");
    }
    {
        ft::vector<std::string> vec;

        vec.push_back("Lorem");
        vec.push_back("ipsum");
        vec.push_back("dolor");
        vec.push_back("sit");
        vec.push_back("amet,");
        vec.push_back("consectetur");

        std::stringstream stream("adipiscing elit, sed");
        std::istream_iterator<std::string> str_it(stream);
        vec.insert(vec.end(), str_it, std::istream_iterator<std::string>());
        assert(vec.size() == 9);
        assert(vec.capacity() >= 9);
        assert(vec[0] == "Lorem");
        assert(vec[1] == "ipsum");
        assert(vec[2] == "dolor");
        assert(vec[3] == "sit");
        assert(vec[4] == "amet,");
        assert(vec[5] == "consectetur");
        assert(vec[6] == "adipiscing");
        assert(vec[7] == "elit,");
        assert(vec[8] == "sed");
    }
    {
        typedef test::limited_allocator<int> allocator;
        ft::vector<int, allocator> vec(100, 42);
        vec.reserve(150);

        allocator::set_limit(allocator::active());
        vec.insert(vec.begin() + 50, test::range_iterator<int>(0),
                   test::range_iterator<int>(50));
        allocator::reset_limit();
    }
    {
        typedef test::limited_allocator<int> allocator;
        ft::vector<int, allocator> vec(test::range_iterator<int>(0),
                                       test::range_iterator<int>(500));

        allocator::set_limit(allocator::active());
        ASSERT_THROW(vec.insert(vec.begin() + 50,
                                test::range_iterator<int>(1000),
                                test::range_iterator<int>(1050)),
                     std::bad_alloc);
        assert(vec.size() == 500);
        assert(vec.capacity() == 500);
        for (size_t idx = 0; idx < 500; ++idx) {
            assert(vec[idx] == static_cast<int>(idx));
        }
        allocator::reset_limit();
    }
    {
        typedef test::throwing_class<test::tracking_class> clazz;
        const ft::vector<clazz> input(10);
        const std::size_t count = test::tracking_class::instances();
        {
            ft::vector<clazz> vec(30);
            clazz::throw_after(5);
            ASSERT_THROW(
                vec.insert(vec.begin() + 10, input.begin(), input.end()),
                test::too_many_instantiations);
        }
        assert(test::tracking_class::instances() == count);
        clazz::reset();
    }
    {
        typedef test::throwing_class<test::tracking_class> clazz;
        const ft::vector<clazz> input(10);
        const std::size_t count = test::tracking_class::instances();
        {
            ft::vector<clazz> vec(30);
            clazz::throw_after(12);
            ASSERT_THROW(
                vec.insert(vec.begin() + 10, input.begin(), input.end()),
                test::too_many_instantiations);
        }
        assert(test::tracking_class::instances() == count);
        clazz::reset();
    }
    {
        typedef test::throwing_class<test::tracking_class> clazz;
        const ft::vector<clazz> input(10);
        const std::size_t count = test::tracking_class::instances();
        {
            ft::vector<clazz> vec(30);
            clazz::throw_after(22);
            ASSERT_THROW(
                vec.insert(vec.begin() + 10, input.begin(), input.end()),
                test::too_many_instantiations);
        }
        assert(test::tracking_class::instances() == count);
        clazz::reset();
    }
    {
        typedef test::throwing_class<test::tracking_class> clazz;
        const ft::vector<clazz> input(10);
        const std::size_t count = test::tracking_class::instances();
        {
            ft::vector<clazz> vec(30);
            clazz::throw_after(3);
            ASSERT_THROW(
                vec.insert(vec.begin() + 25, input.begin(), input.end()),
                test::too_many_instantiations);
        }
        assert(test::tracking_class::instances() == count);
        clazz::reset();
    }
    {
        typedef test::throwing_class<test::tracking_class> clazz;
        const ft::vector<clazz> input(10);
        const std::size_t count = test::tracking_class::instances();
        {
            ft::vector<clazz> vec(30);
            clazz::throw_after(7);
            ASSERT_THROW(
                vec.insert(vec.begin() + 25, input.begin(), input.end()),
                test::too_many_instantiations);
        }
        assert(test::tracking_class::instances() == count);
        clazz::reset();
    }
    {
        typedef test::throwing_class<test::tracking_class> clazz;
        const ft::vector<clazz> input(10);
        const std::size_t count = test::tracking_class::instances();
        {
            ft::vector<clazz> vec(30);
            clazz::throw_after(15);
            ASSERT_THROW(
                vec.insert(vec.begin() + 25, input.begin(), input.end()),
                test::too_many_instantiations);
        }
        assert(test::tracking_class::instances() == count);
        clazz::reset();
    }
    return 0;
}
