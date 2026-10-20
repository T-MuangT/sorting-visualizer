#include <wx/dcmemory.h>
#include <wx/init.h>

#include <iostream>

#include "src/include/SortStats.hpp"
#include "src/include/visualizer/graphics/GraphicsArrayVisualizer.hpp"

int main() {
    wxInitializer app;
    if (!app.IsOk()) return 77;
    GraphicsArrayVisualizer visualizer;
    int refreshes = 0;
    visualizer.setRefreshCallback([&] { ++refreshes; });
    SortStats stats;
    stats.recordEvent(SortEvent::Shift);
    visualizer.renderAuxFrame({3, 1, 2}, AuxEvent::CompareInAux, 1, "aux-bar", "graphics auxiliary smoke", stats);
    wxBitmap bitmap(320, 240);
    wxMemoryDC dc(bitmap);
    visualizer.draw(dc, wxRect(0, 0, 320, 240));
    if (refreshes != 1) return 1;
    std::cout << "Graphics auxiliary visualizer test passed.\n";
}
