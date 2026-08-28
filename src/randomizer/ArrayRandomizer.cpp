#include "../include/ArrayGenerator.hpp"
#include <algorithm>
#include <random>

std::vector<int> ArrayGenerator::generateRandom(
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

    return arr;
}