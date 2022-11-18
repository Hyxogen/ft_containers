#include <__tree/red_black_tree.hpp>
#include <cassert>
#include <memory>
#include <classes.hpp>
#include <allocators.hpp>

template <typename T, typename U>
void insert_and_validate(T &t, const U &u) {
        t.insert(u);
        assert(t.is_valid());
}

int main() {
        typedef ft::detail::rbtree<int, int,
                                   std::allocator<ft::detail::rbnode<int> > >
            irbtree;
        {
                irbtree tree;
        }
        {
                irbtree tree;

                insert_and_validate(tree, 1);
                insert_and_validate(tree, 0);
                insert_and_validate(tree, 2);
        }
        {
                irbtree tree;

                for (int i = 0; i < 100; ++i) {
                        insert_and_validate(tree, i);
                }
        }
        {
                irbtree tree;

                insert_and_validate(tree, 5);
                insert_and_validate(tree, 1);
                insert_and_validate(tree, 9);
                insert_and_validate(tree, 3);
                insert_and_validate(tree, 4);
                insert_and_validate(tree, 10);
                insert_and_validate(tree, 8);
        }
        {
                typedef test::tracking_class clazz;
                typedef ft::detail::rbtree<
                    clazz, clazz, std::allocator<ft::detail::rbnode<clazz> > >
                    rbtree;

                const std::size_t count = clazz::instances();

                {
                        rbtree tree;

                        for (int i = 0; i < 500; i++) {
                                insert_and_validate(tree, clazz(i));
                        }
                }
                assert(count == clazz::instances());
        }
        // TODO add more tests (check if everything is properly deallocated at
        // the end, inserting random values (or semi random at least),
        // exception safety
}
