#include <algorithm>
#include <benchmark.hpp>

int main() {
    set<int> s;

    for (int i = 0; i < 10000; ++i) {
        s.insert(i);
    }

    TIME(DO_NOT_OPTIMIZE(std::find(s.begin(), s.end(), 10000)));
}
