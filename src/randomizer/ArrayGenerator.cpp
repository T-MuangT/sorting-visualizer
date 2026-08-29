#include "../include/ArrayGenerator.hpp"

#include <chrono>
#include <random>

namespace {
uint64_t resolveSeed(uint64_t seed) {
    if (seed != 0) {
        return seed;
    }

    static std::random_device rd;
    static std::mt19937_64 generator(
        static_cast<uint64_t>(std::chrono::high_resolution_clock::now().time_since_epoch().count()) ^
        (static_cast<uint64_t>(rd()) << 1));

    return generator();
}
}  // namespace

std::vector<int> ArrayGenerator::generate(
    size_t size, 
    int minValue, 
    int maxValue, 
    Pattern pattern,
    uint64_t seed) 
{
    const uint64_t effectiveSeed = resolveSeed(seed);

    switch (pattern) {
        case Pattern::ReverseSorted:
            return generateReversed(size, minValue, maxValue, effectiveSeed);
        case Pattern::NearlySorted:
            return generateNearlySorted(size, minValue, maxValue, effectiveSeed);
        case Pattern::UniformRandom:
        default:
            return generateRandom(size, minValue, maxValue, effectiveSeed);
    }
}