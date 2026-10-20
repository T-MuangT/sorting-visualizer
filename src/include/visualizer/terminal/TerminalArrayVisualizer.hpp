#pragma once

#include "../IArrayVisualizer.hpp"

class TerminalArrayVisualizer : public IArrayVisualizer {
private:
    int delayMs;
    void clearScreen() const;
    void renderBars(const std::vector<int>& arr, int idx1, int idx2, char marker) const;
    void waitForNextFrame() const;

public:
    explicit TerminalArrayVisualizer(int delayMs = 100);
    void renderFrame(const std::vector<int>& arr, SortEvent event, int idx1, int idx2, const std::string& stepName, const SortStats& stats) override;
    void renderAuxFrame(const std::vector<int>& arr, AuxEvent event, int highlightedIdx, const std::string& label, const std::string& stepName, const SortStats& stats) override;
};