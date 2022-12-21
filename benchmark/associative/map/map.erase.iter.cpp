#include <benchmark.hpp>
#include <cstdlib>

int main() {
    map<int, int> m;

    for (int i = 0; i < 10000; ++i) {
        const int x = rand() % 5000;
        m[x] = rand();
    }
    TIME(while (!m.empty()) { m.erase(m.begin()); });
}
