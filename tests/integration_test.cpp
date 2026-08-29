#include <algorithm>
#include <iostream>
#include <vector>

#include "../src/include/ArrayGenerator.hpp"
#include "../src/algorithms/exchange-sort/bubble-sort/BubbleSort.hpp"
#include "../src/algorithms/exchange-sort/partition-sort/LomutoQuickSort.hpp"
#include "../src/include/visualizer/TerminalVisualizer.hpp"

int main() {
    auto randomData = ArrayGenerator::generate(64, -50, 50, Pattern::UniformRandom, 99ULL);
    auto sortedByBubble = randomData;
    bubbleSort(sortedByBubble, nullptr);

    if (!std::is_sorted(sortedByBubble.begin(), sortedByBubble.end())) {
        std::cerr << "Integration test failed: bubble sort did not produce sorted data\n";
        return 1;
    }

    auto sortedByQuick = randomData;
    lomutoQuickSort(sortedByQuick, nullptr);

    if (!std::is_sorted(sortedByQuick.begin(), sortedByQuick.end())) {
        std::cerr << "Integration test failed: lomuto quick sort did not produce sorted data\n";
        return 1;
    }

    SortStats stats;
    stats.recordEvent(SortEvent::Compare);
    stats.recordEvent(SortEvent::Swap);

    TerminalVisualizer visualizer(0);
    visualizer.renderFrame(sortedByQuick, SortEvent::Swap, 0, 1, "integration check", stats);

    std::cout << "Integration test passed." << std::endl;
    return 0;
}
