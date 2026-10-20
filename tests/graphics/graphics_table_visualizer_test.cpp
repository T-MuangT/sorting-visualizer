#include <wx/dcmemory.h>
#include <wx/init.h>

#include <iostream>

#include "src/include/SortStats.hpp"
#include "src/include/visualizer/graphics/GraphicsTableVisualizer.hpp"

int main() {
    wxInitializer app;
    if (!app.IsOk()) return 77;
    GraphicsTableVisualizer visualizer;
    int refreshes = 0;
    visualizer.setRefreshCallback([&] { ++refreshes; });
    SortStats stats;
    const std::vector<TableRow> rows = {{"bucket 1", {1, 2}}, {"bucket 2", {}}, {"bucket 3", {3}}};
    visualizer.renderFrame(rows, AuxEvent::PlaceInBucket, {{0, 1}, {2, 0}}, "graphics table smoke", stats);
    wxBitmap bitmap(360, 240);
    wxMemoryDC dc(bitmap);
    visualizer.draw(dc, wxRect(0, 0, 360, 240));
    if (refreshes != 1) return 1;
    std::cout << "Graphics table visualizer test passed.\n";
}
