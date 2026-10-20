#include <iostream>
#include <vector>

#include "../src/include/SortStats.hpp"
#include "../src/include/visualizer/terminal/TerminalArrayVisualizer.hpp"

int main() {
    TerminalArrayVisualizer visualizer(0);
    SortStats stats;
    stats.recordEvent(SortEvent::Compare);
    stats.recordEvent(SortEvent::Swap);
    stats.recordEvent(SortEvent::Shift);
    stats.recordEvent(SortEvent::Insert);

    std::vector<int> auxArray = {3, 1, 2};
    // Render an auxiliary array (bar chart) with a highlighted index
    visualizer.renderAuxFrame(auxArray, AuxEvent::CompareInAux, 1, "aux-bar", "auxiliary visualizer smoke test", stats);

    std::cout << "Auxiliary bar visualizer test passed." << std::endl;
    return 0;
}
