#include <benchmark.hpp>
#include <iterators.hpp>

int main() {
        BENCHMARK(vector<int> tmp; tmp.assign(test::range_iterator<int>(0),
                                              test::range_iterator<int>(500)));
        return 0;
}
