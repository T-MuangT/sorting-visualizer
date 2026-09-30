#include <stdexcept>

#include "../include/visualizer/VisualizationSession.hpp"

VisualizationSession::VisualizationSession(
    IArrayVisualizer& arrayVisualizer,
    ITableVisualizer& tableVisualizer)
    : arrayVisualizer(&arrayVisualizer),
      tableVisualizer(&tableVisualizer)
{
}

void VisualizationSession::resetStats() noexcept {
    stats.reset();
}

const SortStats& VisualizationSession::getStats() const noexcept {
    return stats;
}

const std::vector<TableRow>& VisualizationSession::getAuxRows() const noexcept {
    return auxRows;
}

void VisualizationSession::recordAuxEvent(AuxEvent event) noexcept {
    if (event == AuxEvent::CompareInAux) {
        stats.recordEvent(SortEvent::Compare);
    }
}

std::vector<TableCell> VisualizationSession::highlightedCell(int row, int pos) const {
    if (row < 0 || pos < 0) {
        return {};
    }

    if (row >= static_cast<int>(auxRows.size())) {
        return {};
    }

    if (pos >= static_cast<int>(auxRows[static_cast<size_t>(row)].values.size())) {
        return {};
    }

    return {{row, pos}};
}

void VisualizationSession::ensureRow(int row) {
    if (row < 0) {
        throw std::out_of_range("Auxiliary row cannot be negative.");
    }

    while (row >= static_cast<int>(auxRows.size())) {
        auxRows.push_back({"row " + std::to_string(auxRows.size()), {}});
    }
}

void VisualizationSession::onArrayEvent(const std::vector<int>& arr, SortEvent event, int idx1, int idx2, const std::string& stepName) {
    stats.recordEvent(event);
    arrayVisualizer->renderFrame(arr, event, idx1, idx2, stepName, stats);
}

void VisualizationSession::beginAuxPhase(std::vector<TableRow> initialRows, const std::string& stepName) {
    auxRows = std::move(initialRows);
    tableVisualizer->renderFrame(auxRows, AuxEvent::PlaceInBucket, {}, stepName, stats);
}

// VisualizationSession::onAuxEvent for insertion auxiliary array tables
void VisualizationSession::onAuxEvent(const std::vector<int>& mainArr, AuxEvent event, int srcIdx, int row, int pos, const std::string& stepName) {
    recordAuxEvent(event);

    switch (event) {
        case AuxEvent::PlaceInBucket: {
            if (srcIdx < 0 || srcIdx >= static_cast<int>(mainArr.size())) {
                throw std::out_of_range("Source index is outside the main array.");
            }

            ensureRow(row);
            auto& values = auxRows[static_cast<size_t>(row)].values;
            const int insertPos = (pos < 0 || pos > static_cast<int>(values.size())) ? static_cast<int>(values.size()) : pos;

            values.insert(values.begin() + insertPos, mainArr[static_cast<size_t>(srcIdx)]);
            tableVisualizer->renderFrame(auxRows, event, highlightedCell(row, insertPos), stepName, stats);
            break;
        }

        case AuxEvent::FlushBucket: {
            if (row < 0 || row >= static_cast<int>(auxRows.size())) {
                throw std::out_of_range("Flush row is outside the auxiliary table.");
            }

            auto& values = auxRows[static_cast<size_t>(row)].values;
            if (pos < 0 || pos >= static_cast<int>(values.size())) {
                throw std::out_of_range("Flush position is outside the auxiliary row.");
            }

            tableVisualizer->renderFrame(auxRows, event, highlightedCell(row, pos), stepName, stats);
            values.erase(values.begin() + pos);
            break;
        }

        case AuxEvent::CompareInAux:
            tableVisualizer->renderFrame(auxRows, event, highlightedCell(row, pos), stepName, stats);
            break;

        default:
            throw std::invalid_argument("Invalid event for auxiliary array visualization.");
    }
}

// VisualizationSession::onCountEvent for counting auxiliary array tables
void VisualizationSession::onCountEvent(AuxEvent event, const CountEventData& data, const std::string& stepName) {
    recordAuxEvent(event);

    if (data.countRow < 0 || data.countRow >= static_cast<int>(auxRows.size())) {
        throw std::out_of_range("Count row is outside the auxiliary table.");
    }

    auto& values = auxRows[static_cast<size_t>(data.countRow)].values;

    if (values.empty()) {
        values.push_back(0);
    }

    switch (event) {
        case AuxEvent::IncrementCount: {
            values[0] = data.value;
            tableVisualizer->renderFrame(auxRows, event, highlightedCell(data.countRow, 0), stepName, stats);
            break;
        }

        case AuxEvent::AccumulateCount: {
            values[0] = data.value;
            tableVisualizer->renderFrame(auxRows, event, highlightedCell(data.countRow, 0), stepName, stats);
            break;
        }

        case AuxEvent::PlaceCountOutput: {
            if (data.outputRow < 0 || data.outputRow >= static_cast<int>(auxRows.size())) {
                throw std::out_of_range("Count output row is outside the auxiliary table.");
            }

            if (data.outputPos < 0 || data.outputPos >= static_cast<int>(auxRows[static_cast<size_t>(data.outputRow)].values.size())) {
                throw std::out_of_range("Count output position is outside the auxiliary row.");
            }

            auxRows[static_cast<size_t>(data.outputRow)].values[static_cast<size_t>(data.outputPos)] = data.value;

            tableVisualizer->renderFrame(auxRows, event, {{data.countRow, 0}, {data.outputRow, data.outputPos}}, stepName, stats);

    break;
}

        default:
            throw std::invalid_argument("Invalid event for count array visualization.");
    }
}

void VisualizationSession::endAuxPhase(const std::vector<int>& arr, const std::string& stepName) {
    auxRows.clear();
    arrayVisualizer->renderFrame(arr, SortEvent::Compare, -1, -1, stepName, stats);
}
