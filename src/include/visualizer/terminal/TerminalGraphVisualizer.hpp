#pragma once

#include "../IGraphVisualizer.hpp"

class TerminalGraphVisualizer : public IGraphVisualizer {
private:
    int delayMs;
    int maxVisibleNodes;

    std::vector<TreeNode> lastRenderedNodes;
    AuxEvent lastRenderedEvent = AuxEvent::InsertInTree;
    std::vector<int> lastRenderedHighlights;
    bool hasRenderedGraph = false;

    void clearScreen() const;

    bool isHighlighted(
        const std::vector<int>& highlightedNodes,
        int nodeIdx);

    static const char* eventName(AuxEvent event);
    static char markerFor(AuxEvent event);

    void renderGraph(
        const std::vector<TreeNode>& nodes,
        AuxEvent event,
        const std::vector<int>& highlightedNodes);

public:
    explicit TerminalGraphVisualizer(
        int delayMs = 0,
        int maxVisibleNodes = 15);

    void renderFrame(
        const std::vector<TreeNode>& nodes,
        AuxEvent event,
        const std::vector<int>& highlightedNodes,
        const std::string& stepName,
        const SortStats& stats) override;
};