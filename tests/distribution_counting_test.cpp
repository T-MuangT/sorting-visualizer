#include <algorithm>
#include <iostream>
#include <vector>

#include "include/NoopVisualizers.hpp"
#include "../src/algorithms/distribution-sort/counting-sort/CountingSort.hpp"
#include "../src/include/visualizer/VisualizationSession.hpp"

namespace {
bool verifySort(const std::vector<int>& input) {
    auto data = input;

    NoopArrayVisualizer arrayVisualizer;
    NoopTableVisualizer tableVisualizer;
    NoopGraphVisualizer graphVisualizer;
    VisualizationSession session(arrayVisualizer, tableVisualizer, graphVisualizer);

    countingSort(data, session);

    if (!std::is_sorted(data.begin(), data.end())) {
        std::cerr << "FAIL: Counting Sort produced unsorted output\n";
        return false;
    }

    std::vector<int> expected = input;
    std::sort(expected.begin(), expected.end());

    if (data != expected) {
        std::cerr << "FAIL: Counting Sort produced incorrect values\n";
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
        {5, 0, 2, 9, 1},
        {10, 1, 7, 9, 3, 2, 0},
        {-5, 0, -2, 9, -1},
        {10, -1, 7, -9, 3, 2, 0},
        {9, 8, 7, 6, 5, 4, 3, 2, 1},
        {4, 1, 4, 2, 3, 2, 1, 5},
        {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
        {-3, -1, -3, 2, 0, -1, 2, 2, -3}
    };

    for (const auto& input : cases) {
        if (!verifySort(input)) {
            return 1;
        }
    }

    std::cout << "Counting Sort tests passed." << std::endl;
    return 0;
}