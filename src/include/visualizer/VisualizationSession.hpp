#pragma once

#include <string>
#include <vector>

#include "../SortStats.hpp"
#include "IArrayVisualizer.hpp"
#include "ITableVisualizer.hpp"

class VisualizationSession {
private:
    IArrayVisualizer* arrayVisualizer;
    ITableVisualizer* tableVisualizer;
    SortStats stats;
    std::vector<TableRow> auxRows;

    void recordAuxEvent(AuxEvent event) noexcept;
    [[nodiscard]] std::vector<TableCell> highlightedCell(int row, int pos) const;
    void ensureRow(int row);

public:
    VisualizationSession(IArrayVisualizer& arrayVisualizer, ITableVisualizer& tableVisualizer);

    void resetStats() noexcept;
    [[nodiscard]] const SortStats& getStats() const noexcept;
    [[nodiscard]] const std::vector<TableRow>& getAuxRows() const noexcept;

    void onArrayEvent(
        const std::vector<int>& arr,
        SortEvent event,
        int idx1,
        int idx2,
        const std::string& stepName);

    void beginAuxPhase(
        std::vector<TableRow> initialRows,
        const std::string& stepName);

    void onAuxEvent(
        const std::vector<int>& mainArr,
        AuxEvent event,
        int srcIdx,
        int row,
        int pos,
        const std::string& stepName);

    void endAuxPhase(
        const std::vector<int>& arr,
        const std::string& stepName);
};
