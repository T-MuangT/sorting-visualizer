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
    const std::vector<TableRow> rows = {{"count 1", {2}}, {"count 2", {1}}, {"count 3", {3}}, {"output", {0, 0, 0}}};
    visualizer.renderFrame(rows, AuxEvent::IncrementCount, {{0, 0}}, "graphics count increment", stats);
    visualizer.renderFrame(rows, AuxEvent::AccumulateCount, {{2, 0}}, "graphics count accumulate", stats);
    visualizer.renderFrame(rows, AuxEvent::PlaceCountOutput, {{1, 0}, {3, 1}}, "graphics count output", stats);
    wxBitmap bitmap(360, 260);
    wxMemoryDC dc(bitmap);
    visualizer.draw(dc, wxRect(0, 0, 360, 260));
    if (refreshes != 3) return 1;
    std::cout << "Graphics count visualizer test passed.\n";
}
