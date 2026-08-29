#include <iostream>
#include <vector>

#include "../src/include/SortStats.hpp"
#include "../src/include/visualizer/TerminalVisualizer.hpp"

int main() {
    TerminalVisualizer visualizer(0);
    SortStats stats;
    stats.recordEvent(SortEvent::Compare);
    stats.recordEvent(SortEvent::Swap);

    std::vector<int> array = {3, 1, 2};
    visualizer.renderFrame(array, SortEvent::Compare, 0, 1, "visualizer smoke test", stats);

    std::cout << "Visualizer test passed." << std::endl;
    return 0;
}
