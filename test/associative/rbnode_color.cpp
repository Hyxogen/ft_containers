#include <__tree/red_black_tree.hpp>
#include <cassert>

int main() {
        using namespace ft::detail;
        { assert(rbnode<int>::node_color(NULL) == RB_BLACK); }
        {
                const rbnode<int> node(RB_BLACK);

                assert(rbnode<int>::node_color(&node) == RB_BLACK);
        }
        {
                const rbnode<int> node(RB_RED);

                assert(rbnode<int>::node_color(&node) == RB_RED);
        }
        {
                assert(rbnode<int>(RB_BLACK).black_height() == 1);
        }
        return 0;
}
