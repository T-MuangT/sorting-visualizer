#pragma once

#include <functional>
#include <mutex>
#include <string>
#include <vector>

#include <wx/dc.h>
#include <wx/gdicmn.h>

#include "../IGraphVisualizer.hpp"

class GraphicsGraphVisualizer : public IGraphVisualizer {
private:
    std::vector<TreeNode> nodes;
    std::vector<int> highlightedNodes;
    AuxEvent currentEvent = AuxEvent::InsertInTree;
    std::string stepName;
    SortStats stats;
    std::function<void()> refresh;
    mutable std::mutex stateMutex;

public:
    explicit GraphicsGraphVisualizer();

    ~GraphicsGraphVisualizer() override;

    void initialize();
    void shutdown();
    void setRefreshCallback(std::function<void()> callback);
    void draw(wxDC& dc, const wxRect& bounds) const;

    void renderFrame(const std::vector<TreeNode>& nodes, AuxEvent event, const std::vector<int>& highlightedNodes, const std::string& stepName, const SortStats& stats) override;
};
