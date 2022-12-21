#include <test.hpp>
#include <cassert>

#include <string>

int main() {
    typedef int K;
    typedef std::string V;
    typedef ft::map<K, V> M;

    M m;
    assert(m.size() == 0);

    m[5] = "Hello there";
    assert(m.size() == 1);
    assert(m[5] == "Hello there");

    m[6] = m[5];
    assert(m.size() == 2);
    assert(m[5] == m[6]);

    assert(m[0] == V());
    assert(m.size() == 3);

    m[5] = "42";
    assert(m.size() == 3);
    assert(m[5] == "42");
    assert(m[5] != m[6]);
}
