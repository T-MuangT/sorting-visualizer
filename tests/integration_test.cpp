#include <algorithm>
#include <functional>
#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>

#include "../src/include/AlgorithmRunner.hpp"
#include "../src/include/ArrayGenerator.hpp"
#include "../src/algorithms/exchange-sort/bubble-sort/BubbleSort.hpp"
#include "../src/algorithms/merge-sort/MergeSort.hpp"
#include "../src/algorithms/distribution-sort/counting-sort/CountingSort.hpp"
#include "../src/algorithms/insertion-sort/tree-sort/UnbalancedBstTreeSort.hpp"
#include "../src/include/algorithms/TreeStructure.hpp"
#include "../src/include/visualizer/VisualizationSession.hpp"
#include "../src/include/visualizer/terminal/TerminalArrayVisualizer.hpp"
#include "../src/include/visualizer/terminal/TerminalTableVisualizer.hpp"
#include "../src/include/visualizer/terminal/TerminalGraphVisualizer.hpp"

namespace {

template <typename SortFunction>
bool verifySort(
    const std::vector<int>& input,
    SortFunction&& sortFunction,
    const std::string& label)
{
    auto data = input;

    TerminalArrayVisualizer arrayVisualizer(0);
    TerminalTableVisualizer tableVisualizer(0);
    TerminalGraphVisualizer graphVisualizer(0);

    VisualizationSession session(
        arrayVisualizer,
        tableVisualizer,
        graphVisualizer);

    if constexpr (std::is_invocable_r_v<void, SortFunction, std::vector<int>&, VisualizationSession&>) {
        std::forward<SortFunction>(sortFunction)(data, session);
    } else {
        auto runner = AlgorithmRunner::fromClassic(std::forward<SortFunction>(sortFunction));
        runner(data, session);
    }

    if (!std::is_sorted(data.begin(), data.end())) {
        std::cerr
            << "Integration test failed: "
            << label
            << " did not produce sorted data\n";
        return false;
    }

    return true;
}

}  // namespace

int main() {
    const auto randomData =
        ArrayGenerator::generate(
            64,
            -50,
            50,
            Pattern::UniformRandom,
            99ULL);

    if (!verifySort(randomData, bubbleSort, "Bubble Sort")) {
        return 1;
    }

    if (!verifySort(randomData, mergeSort, "Merge Sort")) {
        return 1;
    }

    if (!verifySort(randomData, countingSort, "Counting Sort")) {
        return 1;
    }

    if (!verifySort(randomData, unbalancedBstTreeSort, "Unbalanced BST Tree Sort")) {
        return 1;
    }

    std::cout << "Integration test passed." << std::endl;
    return 0;
}