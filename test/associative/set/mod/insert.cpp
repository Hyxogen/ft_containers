#include <allocators.hpp>
#include <assert.hpp>
#include <cassert>
#include <classes.hpp>
#include <set.hpp>

template <typename T, typename U>
void check_insert(T &t, const U &u, bool unique) {
        const ft::pair<typename T::iterator, bool> res(t.insert(u));
        if (unique)
                assert(*res.first == u);
        assert(res.second == unique);
}

int main() {
        {
                ft::set<int> set;

                check_insert(set, 42, true);
                check_insert(set, 21, true);
                check_insert(set, 43, true);
                check_insert(set, 42, false);
                check_insert(set, 41, true);
        }
        {
                typedef test::throwing_class<test::tracking_class> clazz;
                ft::set<clazz> set;

                check_insert(set, clazz(11), true);

                std::size_t count = test::tracking_class::instances();
                clazz::throw_after(1);
                ASSERT_THROW(set.insert(clazz(5)),
                             test::too_many_instantiations);
                assert(test::tracking_class::instances() == count);
                clazz::reset();
                check_insert(set, clazz(5), true);

                count = test::tracking_class::instances();
                clazz::throw_after(2);
                ASSERT_THROW(set.insert(clazz(7)),
                             test::too_many_instantiations);
                assert(test::tracking_class::instances() == count);
                clazz::reset();
                check_insert(set, clazz(7), true);

                count = test::tracking_class::instances();
                clazz::throw_after(1);
                check_insert(set, clazz(7), false);
                assert(test::tracking_class::instances() == count);
                clazz::reset();
        }
        {
                typedef test::tracking_class clazz;
                typedef test::limited_allocator<clazz> allocator;
                typedef test::limited_allocator<ft::detail::rbnode<clazz> >
                    node_allocator;
                ft::set<clazz, std::less<clazz>, allocator> set;

                check_insert(set, 51, true);

                node_allocator::set_limit(node_allocator::active());
                const std::size_t count = clazz::instances();
                ASSERT_THROW(set.insert(0), std::bad_alloc);
                assert(clazz::instances() == count);

                node_allocator::reset_limit();
                check_insert(set, 0, true);
        }
        {
                typedef test::tracking_class clazz;

                const std::size_t count = clazz::instances();

                {
                        ft::set<clazz> set;

                        for (int i = 0; i < 500; ++i)
                                check_insert(set, i, true);
                }
                assert(clazz::instances() == count);
        }
}
