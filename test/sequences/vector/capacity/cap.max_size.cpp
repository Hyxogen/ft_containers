#include <test.hpp>
#include <cassert>

int main() {
    typedef ft::vector<int> M;
    M m;

    assert(m.max_size() == m.get_allocator().max_size());
}
