#include "../include/ArrayGenerator.hpp"
#include <algorithm>
#include <random>

std::vector<int> ArrayGenerator::generateNearlySorted(
    size_t size, 
    int minValue, 
    int maxValue, 
    uint64_t seed) 
{
    if (size == 0) return {};

    std::vector<int> arr = generateRandom(size, minValue, maxValue, seed);
    std::sort(arr.begin(), arr.end());

    if (size > 1) {
        std::mt19937_64 rng(seed);
        size_t swaps = std::max<size_t>(1, size / 10);
        std::uniform_int_distribution<size_t> idxDist(0, size - 1);

        for (size_t s = 0; s < swaps; ++s) {
            std::swap(arr[idxDist(rng)], arr[idxDist(rng)]);
        }
    }

    return arr;
}