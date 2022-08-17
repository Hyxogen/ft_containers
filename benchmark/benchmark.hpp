#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include <cstddef>
#include <cstdio>
#include <ctime>
#include <iomanip>
#include <iostream>

#ifndef BENCHMARK_ITER
#define BENCHMARK_ITER 1000000
#elif BENCHMARK_ITER <= 0
#error "BENCHMARK_ITER must be a positive integer"
#endif

#ifdef BENCHMARK_STD
#include <vector>
#define vector std::vector
#else
#include <vector.hpp>
#define vector ft::vector
#endif

#define DO_NOT_OPTIMIZE(statement)                                            \
        asm volatile("" : : "r,m"(statement) : "memory")

#define BENCHMARK(statement)                                                  \
        std::clock_t start = std::clock();                                    \
        for (std::size_t idx = 0; idx < BENCHMARK_ITER; ++idx) {              \
                statement;                                                    \
        };                                                                    \
        std::clock_t end = std::clock();                                      \
        std::printf("%e\n", ((double)(end - start) / BENCHMARK_ITER));

#endif
