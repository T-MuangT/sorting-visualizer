#include <iostream>
#include <vector>

#include "../src/include/SortStats.hpp"
#include "../src/include/visualizer/TerminalTableVisualizer.hpp"

int main() {
    TerminalTableVisualizer visualizer(0);
    SortStats stats;
    stats.recordEvent(SortEvent::Compare);

    const std::vector<TableRow> rows = {
        {"bucket 1", {1, 1}},
        {"bucket 2", {}},
        {"bucket 3", {3}}
    };

    const std::vector<TableCell> highlighted = {
        {0, 1},
        {2, 0}
    };

    visualizer.renderFrame(
        rows,
        AuxEvent::PlaceInBucket,
        highlighted,
        "table visualizer smoke test",
        stats);

    std::cout << "Table visualizer test passed." << std::endl;
    return 0;
}
