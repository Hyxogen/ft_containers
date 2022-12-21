#include <benchmark.hpp>
#include <cstdlib>

int main() {
    set<int> st;
    BENCHMARK(DO_NOT_OPTIMIZE(st.insert(rand() % 1000)));
    DO_NOT_OPTIMIZE(st);
    return 0;
}
