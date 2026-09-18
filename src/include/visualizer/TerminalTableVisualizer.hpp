#pragma once

#include "ITableVisualizer.hpp"

class TerminalTableVisualizer : public ITableVisualizer {
private:
    int delayMs;

    void clearScreen() const;
    static bool isHighlighted(const std::vector<TableCell>& highlighted, int row, int pos);
    static const char* eventName(AuxEvent event);
    static char markerFor(AuxEvent event);

public:
    explicit TerminalTableVisualizer(int delayMs = 100);

    void renderFrame(
        const std::vector<TableRow>& rows,
        AuxEvent event,
        const std::vector<TableCell>& highlighted,
        const std::string& stepName,
        const SortStats& stats) override;
};
