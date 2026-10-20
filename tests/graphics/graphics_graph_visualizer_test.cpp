#include <wx/dcmemory.h>
#include <wx/init.h>

#include <iostream>
#include <vector>

#include "src/include/SortStats.hpp"
#include "src/include/visualizer/graphics/GraphicsGraphVisualizer.hpp"

int main() {
    wxInitializer app;
    if (!app.IsOk()) return 77;
    GraphicsGraphVisualizer visualizer;
    int refreshes = 0;
    visualizer.setRefreshCallback([&] { ++refreshes; });
    SortStats stats;
    const std::vector<TreeNode> nodes = {{5, -1, 1, 2}, {3, 0, 3, 4}, {7, 0, -1, 5}, {2, 1, -1, -1}, {4, 1, -1, -1}, {8, 2, -1, -1}};
    visualizer.renderFrame(nodes, AuxEvent::VisitInOrder, {1, 3}, "graphics graph smoke", stats);
    wxBitmap bitmap(360, 260);
    wxMemoryDC dc(bitmap);
    visualizer.draw(dc, wxRect(0, 0, 360, 260));
    if (refreshes != 1) return 1;
    std::cout << "Graphics graph visualizer test passed.\n";
}
