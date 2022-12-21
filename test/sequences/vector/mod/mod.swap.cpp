#include <test.hpp>
#include <allocators.hpp>
#include <cassert>
#include <classes.hpp>

int main() {
    {
        ft::vector<int> a, b;
        a.push_back(2);
        a.push_back(3);
        a.push_back(5);
        a.push_back(7);
        b.push_back(1);
        b.push_back(4);
        b.push_back(6);
        b.push_back(8);
        b.push_back(9);

        std::size_t acap = a.capacity(), bcap = b.capacity();
        a.swap(b);
        assert(a.capacity() == bcap);
        assert(b.capacity() == acap);
        assert(a.size() == 5);
        assert(b.size() == 4);

        assert(a[0] == 1);
        assert(a[1] == 4);
        assert(a[2] == 6);
        assert(a[3] == 8);
        assert(a[4] == 9);
        assert(b[0] == 2);
        assert(b[1] == 3);
        assert(b[2] == 5);
        assert(b[3] == 7);
    }
    {
        typedef test::throwing_class<int> clazz;
        typedef test::limited_allocator<clazz> allocator;
        ft::vector<clazz, allocator> a, b;
        a.push_back(test::throwing_class<int>(5));
        a.push_back(test::throwing_class<int>(862));
        a.push_back(test::throwing_class<int>(3124));
        a.push_back(test::throwing_class<int>(9438));
        b.push_back(test::throwing_class<int>(742));
        b.push_back(test::throwing_class<int>(486));
        b.push_back(test::throwing_class<int>(14));
        b.push_back(test::throwing_class<int>(5342));
        clazz::make_next_throw();
        allocator::set_limit(test::allocator_tracker<clazz>::active());
        a.swap(b);
    }
    return 0;
}
