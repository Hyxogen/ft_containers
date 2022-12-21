#include <cassert>
#include <map.hpp>
#include <string>

int main() {
    typedef ft::map<int, std::string> M;
    typedef M::value_type P;

    P a[] = {
        P(1, "Hi"),         P(2, "There"), P(3, "ft"),
        P(4, "containers"), P(5, "thing"), P(6, "stuff"),
    };

    const M::size_type s = sizeof(a) / sizeof(a[0]);
    M m(a, a + s);
    assert(m.size() == s);
    m.clear();
    assert(m.size() == 0);
}
