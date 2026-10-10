#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

#include "../src/include/algorithms/PairwiseCompareSwap.hpp"
#include "../src/include/algorithms/ArraySplitRange.hpp"
#include "../src/include/algorithms/PivotSelection.hpp"
#include "../src/algorithms/exchange-sort/partition-sort/DualPivotQuickSort.hpp"

namespace {

using SortFunc = void (*)(std::vector<int>&, SortCallback, DualPivotSelector);

// Changed parameter name from 'selectors' to 'selector' (singular)
bool verifySort(SortFunc fn, const std::vector<int>& input, const std::string& label, DualPivotSelector selector) {
    auto data = input;

    fn(data, nullptr, selector);

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
        {"dualPivotQuickSort", static_cast<SortFunc>(dualPivotQuickSort)}
    };

    const std::vector<std::pair<std::string, DualPivotSelector>> selectors = {
        {"FirstAndLastIndices", firstAndLastIndicesPivots},
        {"TwoRandomIndices", twoRandomIndicesPivots},
        {"TwoQuartileMedians", twoQuartileMediansPivots}
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

    for (const auto& [algLabel, fn] : algorithms) {
        // Changed loop variable from 'selectors' to 'selector' to avoid hiding the outer vector
        for (const auto& [selLabel, selector] : selectors) {
            std::string fullLabel = algLabel + " (" + selLabel + ")";
            for (const auto& input : cases) {
                if (!verifySort(fn, input, fullLabel, selector)) {
                    return 1;
                }
            }
        }
    }

    std::cout << "Dual-Pivot Quicksort tests passed successfully." << std::endl;
    return 0;
}