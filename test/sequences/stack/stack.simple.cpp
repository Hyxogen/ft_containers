#include <cassert>
#include <test.hpp>

int main() {
    typedef ft::stack<int> C;

    C c = C();
    assert(c.empty());
    assert(c.size() == 0);

    assert(c == C());

    c.push(5);
    assert(c.size() == 1);
    assert(c.top() == 5);

    C c2 = C();

    c2 = c;
    c.pop();
    assert(c.size() == 0);

    assert(c2.size() == 1);
    assert(c2.top() == 5);

    assert(c != c2);
}
