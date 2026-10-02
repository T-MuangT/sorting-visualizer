#include <algorithm>
#include <iostream>
#include <vector>

#include "include/NoopVisualizers.hpp"
#include "../src/algorithms/merge-sort/MergeSort.hpp"
#include "../src/include/visualizer/VisualizationSession.hpp"

namespace {
bool verifySort(const std::vector<int>& input) {
    auto data = input;

    NoopArrayVisualizer arrayVisualizer;
    NoopTableVisualizer tableVisualizer;
    NoopGraphVisualizer graphVisualizer;
    VisualizationSession session(arrayVisualizer, tableVisualizer, graphVisualizer);

    mergeSort(data, session);

    std::vector<int> expected = input;
    std::sort(expected.begin(), expected.end());

    if (data != expected) {
        std::cerr << "FAIL: Mergesort produced incorrect output\n";
        return false;
    }

    return true;
}
}  // namespace

int main() {
    const std::vector<std::vector<int>> cases = {
        {},
        {42},
        {5, 4, 3, 2, 1},
        {1, 2, 3, 4, 5},
        {3, 1, 3, 2, 1},
        {-5, 0, -2, 9, -1},
        {10, -1, 7, -9, 3, 2, 0},
        {9, 8, 7, 6, 5, 4, 3, 2, 1},
        {4, 1, 4, 2, 3, 2, 1, 5},
        {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}
    };

    for (const auto& input : cases) {
        if (!verifySort(input)) {
            return 1;
        }
    }

    std::cout << "Mergesort tests passed." << std::endl;
    return 0;
}
