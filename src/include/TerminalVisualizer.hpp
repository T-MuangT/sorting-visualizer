#pragma once

#include <vector>
#include <string>
#include "Types.hpp"

class TerminalVisualizer {
private:
    int delayMs;

    void clearScreen() const;

public:
    explicit TerminalVisualizer(int delayMs = 100);

    // Event handler for all sorting renderings
    void onSortEvent(
        const std::vector<int>& arr,
        SortEvent event,
        int idx1,
        int idx2,
        const std::string& stepName);
};