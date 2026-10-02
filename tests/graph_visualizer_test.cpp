#include <iostream>
#include <vector>

#include "../src/include/SortStats.hpp"
#include "../src/include/visualizer/TerminalGraphVisualizer.hpp"

int main() {
    TerminalGraphVisualizer visualizer(0);

    SortStats stats;
    stats.recordEvent(SortEvent::Compare);

    const std::vector<TreeNode> nodes = {
        {5, -1, 1, 2},
        {3, 0, 3, 4},
        {7, 0, -1, 5},
        {2, 1, -1, -1},
        {4, 1, -1, -1},
        {8, 2, -1, -1}
    };

    const std::vector<int> highlighted = {
        1,
        3
    };

    visualizer.renderFrame(
        nodes,
        AuxEvent::VisitInOrder,
        highlighted,
        "graph visualizer test",
        stats);

    std::cout << "Graph visualizer test passed." << std::endl;
    return 0;
}