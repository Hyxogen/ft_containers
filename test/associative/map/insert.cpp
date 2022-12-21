#include <allocators.hpp>
#include <assert.hpp>
#include <cassert>
#include <classes.hpp>
#include <map.hpp>
#include <ostream>
#include <utility.hpp>

template <typename T>
void check_insert(T &t, const typename T::value_type &u, bool unique) {
    const ft::pair<typename T::iterator, bool> res(t.insert(u));
    if (unique)
        assert(*res.first == u);
    else
        assert((*res.first).first == u.first);
    assert(res.second == unique);
}

template <typename T>
void check_insert(T &t, const typename T::value_type::first_type &x,
                  const typename T::value_type::second_type &y, bool unique) {
    check_insert(t, typename T::value_type(x, y), unique);
}

int main() {
    {
        ft::map<int, int> map;

        check_insert(map, 4, 42, true);
        check_insert(map, 5, 42, true);
        check_insert(map, 4, 0, false);
        check_insert(map, 0, 0, true);
    }
    {
        typedef test::throwing_class<test::tracking_class> clazz;
        ft::map<int, clazz> map;

        check_insert(map, 2, clazz(7), true);

        std::size_t count = test::tracking_class::instances();
        clazz::throw_after(2);
        ASSERT_THROW(map.insert(ft::map<int, clazz>::value_type(0, clazz(8))),
                     test::too_many_instantiations);
        assert(test::tracking_class::instances() == count);
        clazz::reset();
        check_insert(map, 0, clazz(8), true);

        count = test::tracking_class::instances();
        clazz::throw_after(3);
        ASSERT_THROW(map.insert(ft::map<int, clazz>::value_type(9, clazz(342))),
                     test::too_many_instantiations);
        assert(test::tracking_class::instances() == count);
        clazz::reset();
        check_insert(map, 9, clazz(53), true);

        count = test::tracking_class::instances();
        clazz::throw_after(2);
        check_insert(map, 9, clazz(53), false);
        assert(test::tracking_class::instances() == count);
        clazz::reset();
    }
    {
        typedef test::throwing_class<test::tracking_class> clazz;
        ft::map<clazz, int> map;

        check_insert(map, clazz(2), 7, true);

        std::size_t count = test::tracking_class::instances();
        clazz::throw_after(2);
        ASSERT_THROW(map.insert(ft::map<clazz, int>::value_type(clazz(0), 8)),
                     test::too_many_instantiations);
        assert(test::tracking_class::instances() == count);
        clazz::reset();
        check_insert(map, clazz(0), 8, true);

        count = test::tracking_class::instances();
        clazz::throw_after(3);
        ASSERT_THROW(map.insert(ft::map<clazz, int>::value_type(clazz(9), 342)),
                     test::too_many_instantiations);
        assert(test::tracking_class::instances() == count);
        clazz::reset();
        check_insert(map, clazz(9), 53, true);

        count = test::tracking_class::instances();
        clazz::throw_after(2);
        check_insert(map, clazz(9), 53, false);
        assert(test::tracking_class::instances() == count);
        clazz::reset();
    }
    {
        typedef test::tracking_class clazz;
        typedef test::limited_allocator<clazz> allocator;
        typedef test::limited_allocator<
            ft::detail::rbnode<ft::pair<const int, clazz> > >
            node_allocator;
        ft::map<int, clazz, std::less<clazz>, allocator> map;

        check_insert(map, 52, 51, true);
        node_allocator::set_limit(node_allocator::active());
        const std::size_t count = clazz::instances();
        ASSERT_THROW(
            map.insert(
                ft::map<int, clazz, std::less<clazz>, allocator>::value_type(
                    34, 2)),
            std::bad_alloc);
        assert(clazz::instances() == count);

        node_allocator::reset_limit();
    }
    {
        typedef test::tracking_class clazz;
        typedef test::limited_allocator<
            ft::detail::rbnode<ft::pair<const int, clazz> > >
            node_allocator;

        const std::size_t count = clazz::instances();
        const std::size_t active = node_allocator::active();

        {
            ft::map<int, clazz> map;

            for (int i = 0; i < 500; ++i) {
                check_insert(map, i, i, true);
            }
        }
        assert(clazz::instances() == count);
        assert(node_allocator::active() == active);
    }
}
