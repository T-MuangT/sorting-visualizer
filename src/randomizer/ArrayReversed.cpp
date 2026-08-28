#include "../include/ArrayGenerator.hpp"
#include <algorithm>
#include <random>

std::vector<int> ArrayGenerator::generateReversed(
    size_t size, 
    int minValue, 
    int maxValue, 
    uint64_t seed) 
{
    std::vector<int> arr(size);
    std::mt19937_64 rng(seed);
    std::uniform_int_distribution<int> dist(minValue, maxValue);

    for (size_t i = 0; i < size; ++i) {
        arr[i] = dist(rng);
    }

    // Sort in strictly descending order
    std::sort(arr.begin(), arr.end(), std::greater<int>());

    return arr;
}