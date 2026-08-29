#include <algorithm>
#include <iostream>
#include <vector>

#include "../src/algorithms/exchange-sort/bubble-sort/BubbleSort.hpp"
#include "../src/algorithms/exchange-sort/bubble-sort/CocktailShakerSort.hpp"
#include "../src/algorithms/exchange-sort/bubble-sort/OptimizedCocktailShakerSort.hpp"
#include "../src/algorithms/exchange-sort/bubble-sort/OddEvenSort.hpp"
#include "../src/algorithms/exchange-sort/bubble-sort/OptimizedOddEvenSort.hpp"
#include "../src/algorithms/exchange-sort/bubble-sort/CombSort.hpp"
#include "../src/algorithms/exchange-sort/bubble-sort/OptimizedCombSort.hpp"

namespace {

using SortFunc = void (*)(std::vector<int>&, SortCallback);

bool verifySort(SortFunc fn, const std::vector<int>& input, const std::string& label) {
    auto data = input;
    fn(data, nullptr);
    if (!std::is_sorted(data.begin(), data.end())) {
        std::cerr << "FAIL: " << label << " produced unsorted output\n";
        return false;
    }

    std::vector<int> expected = input;
    std::sort(expected.begin(), expected.end());
    if (data != expected) {
        std::cerr << "FAIL: " << label << " produced incorrect values\n";
        return false;
    }

    return true;
}

}  // namespace

int main() {
    const std::vector<std::pair<std::string, SortFunc>> algorithms = {
        {"bubbleSort", bubbleSort},
        {"cocktailShakerSort", cocktailShakerSort},
        {"optimizedCocktailShakerSort", optimizedCocktailShakerSort},
        {"oddEvenSort", oddEvenSort},
        {"optimizedOddEvenSort", optimizedOddEvenSort},
        {"combSort", combSort},
        {"optimizedCombSort", optimizedCombSort}
    };

    const std::vector<std::vector<int>> cases = {
        {},
        {42},
        {5, 4, 3, 2, 1},
        {1, 2, 3, 4, 5},
        {3, 1, 3, 2, 1},
        {-5, 0, -2, 9, -1},
        {10, -1, 7, -9, 3, 2, 0},
        {1, 2, 3, 5, 4, 6, 7, 8},
        {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}
    };

    for (const auto& [label, fn] : algorithms) {
        for (const auto& input : cases) {
            if (!verifySort(fn, input, label)) {
                return 1;
            }
        }
    }

    std::cout << "Exchange bubble tests passed." << std::endl;
    return 0;
}
