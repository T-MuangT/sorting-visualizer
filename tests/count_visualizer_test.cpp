#include <iostream>
#include <vector>

#include "../src/include/SortStats.hpp"
#include "../src/include/algorithms/CountEventData.hpp"
#include "../src/include/visualizer/terminal/TerminalTableVisualizer.hpp"

int main() {
    TerminalTableVisualizer visualizer(0);

    SortStats stats;

    const std::vector<TableRow> rows = {
        {"count 1", {2}},
        {"count 2", {1}},
        {"count 3", {3}},
        {"output", {0, 0, 0}}
    };

    visualizer.renderFrame(
        rows,
        AuxEvent::IncrementCount,
        {{0, 0}},
        "count visualizer increment test",
        stats);

    visualizer.renderFrame(
        rows,
        AuxEvent::AccumulateCount,
        {{2, 0}},
        "count visualizer accumulate test",
        stats);

    visualizer.renderFrame(
        rows,
        AuxEvent::PlaceCountOutput,
        {{1, 0}, {3, 1}},
        "count visualizer output test",
        stats);

    std::cout << "Count visualizer test passed." << std::endl;
    return 0;
}