#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

#include "../src/include/Types.hpp"
#include "../src/algorithms/exchange-sort/bubble-sort/BubbleSort.hpp"
#include "../src/algorithms/exchange-sort/bubble-sort/CocktailShakerSort.hpp"
#include "../src/algorithms/exchange-sort/bubble-sort/OptimizedCocktailShakerSort.hpp"
#include "../src/algorithms/exchange-sort/bubble-sort/OddEvenSort.hpp"
#include "../src/algorithms/exchange-sort/bubble-sort/CombSort.hpp"
#include "../src/algorithms/exchange-sort/bubble-sort/OptimizedCombSort.hpp"
#include "../src/algorithms/exchange-sort/partition-sort/CircleSort.hpp"
#include "../src/algorithms/exchange-sort/partition-sort/LomutoQuickSort.hpp"
#include "../src/algorithms/exchange-sort/partition-sort/HoareQuickSort.hpp"
#include "../src/algorithms/exchange-sort/partition-sort/DualPivotQuickSort.hpp"
#include "../src/algorithms/exchange-sort/partition-sort/StableQuickSort.hpp"

using SortFunc = void (*)(std::vector<int>&, SortCallback);

namespace {

std::vector<int> makeRandomInput(size_t size) {
    std::mt19937 rng(12345);
    std::uniform_int_distribution<int> dist(-1000, 1000);
    std::vector<int> values(size);
    for (int& value : values) {
        value = dist(rng);
    }
    return values;
}

bool verifyResult(const std::vector<int>& original, const std::vector<int>& actual, const std::string& label) {
    std::vector<int> expected = original;
    std::sort(expected.begin(), expected.end());

    if (actual != expected) {
        std::cerr << "FAIL: " << label << "\n"
                  << "  expected: ";
        for (int value : expected) std::cerr << value << ' ';
        std::cerr << "\n  actual:   ";
        for (int value : actual) std::cerr << value << ' ';
        std::cerr << "\n";
        return false;
    }

    return true;
}

bool runCase(const std::string& algorithmName, SortFunc fn, const std::vector<int>& input) {
    auto original = input;
    auto working = input;

    fn(working, nullptr);

    if (!std::is_sorted(working.begin(), working.end())) {
        std::cerr << "FAIL: " << algorithmName << " produced unsorted data for input size "
                  << input.size() << "\n";
        return false;
    }

    return verifyResult(original, working, algorithmName + " | size=" + std::to_string(input.size()));
}

} // namespace

int main() {
    const std::vector<SortFunc> algorithms = {
        bubbleSort,
        cocktailShakerSort,
        optimizedCocktailShakerSort,
        oddEvenSort,
        combSort,
        optimizedCombSort,
        circleSort,
        lomutoQuickSort,
        hoareQuickSort,
        dualPivotQuickSort,
        stableQuickSort
    };

    const std::vector<std::vector<int>> testCases = {
        {},
        {42},
        {1, 2, 3, 4, 5, 6},
        {9, 8, 7, 6, 5, 4, 3, 2, 1},
        {3, 1, 3, 2, 1},
        {-5, 0, -2, 9, -1, 7},
        {10, -1, 7, -9, 3, 2, 0},
        {1, 2, 3, 5, 4, 6, 7, 8},
        {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
        makeRandomInput(100),
        makeRandomInput(1000)
    };

    const std::vector<std::string> algorithmNames = {
        "bubbleSort",
        "cocktailShakerSort",
        "optimizedCocktailShakerSort",
        "oddEvenSort",
        "combSort",
        "optimizedCombSort",
        "circleSort",
        "lomutoQuickSort",
        "hoareQuickSort",
        "dualPivotQuickSort",
        "stableQuickSort"
    };

    for (size_t i = 0; i < algorithms.size(); ++i) {
        for (const auto& input : testCases) {
            if (!runCase(algorithmNames[i], algorithms[i], input)) {
                return 1;
            }
        }
    }

    std::cout << "All sorting algorithm tests passed." << std::endl;
    return 0;
}
