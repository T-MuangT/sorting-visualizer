#include <algorithm>
#include <iostream>
#include <vector>

#include "../src/algorithms/distribution-sort/pigeonhole-sort/PigeonholeSort.hpp"
#include "../src/include/visualizer/TerminalArrayVisualizer.hpp"
#include "../src/include/visualizer/TerminalTableVisualizer.hpp"
#include "../src/include/visualizer/VisualizationSession.hpp"

namespace {

bool verifySort(const std::vector<int>& input) {
    auto data = input;

    TerminalArrayVisualizer arrayVisualizer(0);
    TerminalTableVisualizer tableVisualizer(0);
    VisualizationSession session(arrayVisualizer, tableVisualizer);

    pigeonholeSort(data, session);

    if (!std::is_sorted(data.begin(), data.end())) {
        std::cerr << "FAIL: pigeonholeSort produced unsorted output\n";
        return false;
    }

    std::vector<int> expected = input;
    std::sort(expected.begin(), expected.end());
    if (data != expected) {
        std::cerr << "FAIL: pigeonholeSort produced incorrect values\n";
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

    std::cout << "Pigeonhole sort tests passed." << std::endl;
    return 0;
}
