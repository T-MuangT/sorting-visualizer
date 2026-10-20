#pragma once

#include <wx/frame.h>

#include <atomic>

#include "GraphicsArrayVisualizer.hpp"
#include "GraphicsTableVisualizer.hpp"
#include "GraphicsGraphVisualizer.hpp"

class wxPanel;

class GraphicsVisualizerDashboard : public wxFrame {
private:
    void createMenuBar();
    void createControls();
    void createLayout();

    wxPanel* mainArrayPanel = nullptr;
    wxPanel* tablePanel = nullptr;
    wxPanel* graphPanel = nullptr;

    GraphicsArrayVisualizer arrayVisualizer;
    GraphicsTableVisualizer tableVisualizer;
    GraphicsGraphVisualizer graphVisualizer;
    int frameDelayMs = 0;
    std::atomic<bool> refreshPending{false};
    bool sortingRunning = false;

    void requestRefresh();

public:
    explicit GraphicsVisualizerDashboard(wxWindow* parent, const wxString& title);
    ~GraphicsVisualizerDashboard() override;

    [[nodiscard]] GraphicsArrayVisualizer& getArrayVisualizer() noexcept;
    [[nodiscard]] GraphicsTableVisualizer& getTableVisualizer() noexcept;
    [[nodiscard]] GraphicsGraphVisualizer& getGraphVisualizer() noexcept;
    void setFrameDelay(int delayMs) noexcept;
    void setSortingRunning(bool running) noexcept;
};
