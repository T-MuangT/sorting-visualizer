#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

#include "../src/include/ArrayGenerator.hpp"

namespace {

bool sameElements(const std::vector<int>& lhs, const std::vector<int>& rhs) {
    std::vector<int> l = lhs;
    std::vector<int> r = rhs;
    std::sort(l.begin(), l.end());
    std::sort(r.begin(), r.end());
    return l == r;
}

}  // namespace

int main() {
    const size_t size = 64;
    const int minValue = -250;
    const int maxValue = 250;

    auto randomValues = ArrayGenerator::generateRandom(size, minValue, maxValue, 1234ULL);
    if (randomValues.size() != size) {
        std::cerr << "Random values size mismatch\n";
        return 1;
    }

    auto reversedValues = ArrayGenerator::generateReversed(size, minValue, maxValue, 1234ULL);
    if (!std::is_sorted(reversedValues.begin(), reversedValues.end(), std::greater<int>())) {
        std::cerr << "Reversed values not descending\n";
        return 1;
    }

    auto nearlySortedValues = ArrayGenerator::generateNearlySorted(size, minValue, maxValue, 1234ULL);
    if (nearlySortedValues.size() != size) {
        std::cerr << "Nearly sorted values size mismatch\n";
        return 1;
    }

    const auto patternRandom = ArrayGenerator::generate(size, minValue, maxValue, Pattern::UniformRandom, 1234ULL);
    const auto patternReverse = ArrayGenerator::generate(size, minValue, maxValue, Pattern::ReverseSorted, 1234ULL);
    const auto patternNearly = ArrayGenerator::generate(size, minValue, maxValue, Pattern::NearlySorted, 1234ULL);

    if (patternRandom.size() != size || patternReverse.size() != size || patternNearly.size() != size) {
        std::cerr << "Pattern generator size mismatch\n";
        return 1;
    }

    if (!sameElements(patternRandom, randomValues)) {
        std::cerr << "Uniform random pattern differs from generateRandom\n";
        return 1;
    }

    if (!std::is_sorted(patternReverse.begin(), patternReverse.end(), std::greater<int>())) {
        std::cerr << "Reverse pattern is not descending\n";
        return 1;
    }

    std::cout << "Randomizer tests passed." << std::endl;
    return 0;
}
