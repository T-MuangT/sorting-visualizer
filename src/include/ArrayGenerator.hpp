#pragma once

#include <vector>
#include <cstddef>
#include <cstdint>

enum class Pattern {
    UniformRandom,
    ReverseSorted,
    NearlySorted
};

class ArrayGenerator {
public:
    static std::vector<int> generate(
        size_t size, 
        int minValue, 
        int maxValue, 
        Pattern pattern = Pattern::UniformRandom,
        uint64_t seed = 0);

    static std::vector<int> generateRandom(size_t size, int minValue, int maxValue, uint64_t seed);
    static std::vector<int> generateReversed(size_t size, int minValue, int maxValue, uint64_t seed);
    static std::vector<int> generateNearlySorted(size_t size, int minValue, int maxValue, uint64_t seed);
};