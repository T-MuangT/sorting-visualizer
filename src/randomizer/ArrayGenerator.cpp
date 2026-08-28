#include "../include/ArrayGenerator.hpp"

std::vector<int> ArrayGenerator::generate(
    size_t size, 
    int minValue, 
    int maxValue, 
    Pattern pattern,
    uint64_t seed) 
{
    switch (pattern) {
        case Pattern::ReverseSorted:
            return generateReversed(size, minValue, maxValue, seed);
        case Pattern::NearlySorted:
            return generateNearlySorted(size, minValue, maxValue, seed);
        case Pattern::UniformRandom:
        default:
            return generateRandom(size, minValue, maxValue, seed);
    }
}