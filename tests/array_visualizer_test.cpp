#include <iostream>
#include <vector>

#include "../src/include/SortStats.hpp"
#include "../src/include/visualizer/TerminalArrayVisualizer.hpp"

int main() {
    TerminalArrayVisualizer visualizer(0);
    SortStats stats;
    stats.recordEvent(SortEvent::Compare);
    stats.recordEvent(SortEvent::Swap);
    stats.recordEvent(SortEvent::Shift);
    stats.recordEvent(SortEvent::Insert);

    std::vector<int> array = {3, 1, 2};
    visualizer.renderFrame(array, SortEvent::Compare, 0, 1, "visualizer smoke test", stats);

    std::cout << "Array visualizer test passed." << std::endl;
    return 0;
}
