#include <wx/dcmemory.h>
#include <wx/init.h>

#include <algorithm>
#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>

#include "src/include/AlgorithmRunner.hpp"
#include "src/include/ArrayGenerator.hpp"
#include "src/algorithms/exchange-sort/bubble-sort/BubbleSort.hpp"
#include "src/algorithms/merge-sort/MergeSort.hpp"
#include "src/algorithms/distribution-sort/counting-sort/CountingSort.hpp"
#include "src/algorithms/insertion-sort/tree-sort/UnbalancedBstTreeSort.hpp"
#include "src/include/visualizer/VisualizationSession.hpp"
#include "src/include/visualizer/graphics/GraphicsArrayVisualizer.hpp"
#include "src/include/visualizer/graphics/GraphicsGraphVisualizer.hpp"
#include "src/include/visualizer/graphics/GraphicsTableVisualizer.hpp"

namespace {
    template <typename SortFunction>
    bool verifySort(
        const std::vector<int>& input,
        SortFunction&& sortFunction,
        const char* label,
        bool expectAuxiliaryFrames
    ) {
        auto data = input;

        GraphicsArrayVisualizer arrayVisualizer;
        GraphicsTableVisualizer tableVisualizer;
        GraphicsGraphVisualizer graphVisualizer;

        int arrayFrames = 0;
        int tableFrames = 0;
        int graphFrames = 0;

        arrayVisualizer.setRefreshCallback([&] { ++arrayFrames; });
        tableVisualizer.setRefreshCallback([&] { ++tableFrames; });
        graphVisualizer.setRefreshCallback([&] { ++graphFrames; });

        VisualizationSession session(
            arrayVisualizer,
            tableVisualizer,
            graphVisualizer
        );

        if constexpr (
            std::is_invocable_r_v<
            void,
            SortFunction,
            std::vector<int>&,
            VisualizationSession&
            >
            ) {
            std::forward<SortFunction>(sortFunction)(data, session);
        }
        else {
            auto runner = AlgorithmRunner::fromClassic(
                std::forward<SortFunction>(sortFunction)
            );
            runner(data, session);
        }

        const bool sorted = std::is_sorted(data.begin(), data.end());
        const bool arrayRefreshed = arrayFrames > 0;
        const bool auxiliaryRefreshed =
            (tableFrames + graphFrames) > 0;

        std::cout
            << label
            << ": sorted=" << sorted
            << ", arrayFrames=" << arrayFrames
            << ", tableFrames=" << tableFrames
            << ", graphFrames=" << graphFrames
            << '\n';

        return sorted
            && arrayRefreshed
            && (!expectAuxiliaryFrames || auxiliaryRefreshed);
    }
}

int main() {
    wxInitializer app;
    if (!app.IsOk()) {
        return 77;
    }

    const auto data = ArrayGenerator::generate(
        64, -50, 50, Pattern::UniformRandom, 99ULL
    );

    if (!verifySort(data, bubbleSort, "Bubble Sort", false) ||
        !verifySort(data, mergeSort, "Merge Sort", false) ||
        !verifySort(data, countingSort, "Counting Sort", true) ||
        !verifySort(
            data,
            unbalancedBstTreeSort,
            "Unbalanced BST Tree Sort",
            true
        )) {
        std::cerr << "Graphics integration test failed.\n";
        return 1;
    }

    std::cout << "Graphics integration test passed.\n";
    return 0;
}