#pragma once

#include <string>
#include <vector>

#include "../SortStats.hpp"
#include "../algorithms/PartitionEventData.hpp"
#include "../algorithms/PartitionArray.hpp"
// #include "../algorithms/BucketEventData.hpp"    // TODO: Add Bucket Event Data for Visualization Session
#include "../algorithms/CountEventData.hpp"
#include "../algorithms/TreeEventData.hpp"
#include "IArrayVisualizer.hpp"
#include "ITableVisualizer.hpp"
#include "IGraphVisualizer.hpp"

class VisualizationSession {
private:
    IArrayVisualizer* arrayVisualizer;
    ITableVisualizer* tableVisualizer;
    IGraphVisualizer* graphVisualizer;
    SortStats stats;
    std::vector<PartitionArray> partitionArrays;
    std::vector<TableRow> auxRows;
    std::vector<TreeNode> treeNodes;

    void recordAuxEvent(AuxEvent event) noexcept;
    [[nodiscard]] std::vector<TableCell> highlightedCell(int row, int pos) const;
    void ensureRow(int row);

public:
    VisualizationSession(IArrayVisualizer& arrayVisualizer, ITableVisualizer& tableVisualizer, IGraphVisualizer& graphVisualizer);

    void resetStats() noexcept;
    [[nodiscard]] const SortStats& getStats() const noexcept;
    [[nodiscard]] const std::vector<PartitionArray>& getPartitionArrays() const noexcept;
    [[nodiscard]] const std::vector<TableRow>& getAuxRows() const noexcept;
    [[nodiscard]] const std::vector<TreeNode>& getTreeNodes() const noexcept;

    void onArrayEvent(const std::vector<int>& arr, SortEvent event, int idx1, int idx2, const std::string& stepName);

    void beginPartitionPhase(std::vector<PartitionArray> initialArrays, const std::string& stepName);
    void onPartitionEvent(const std::vector<int>& mainArr, const PartitionEventData& data, const std::string& stepName);
    void endPartitionPhase(const std::vector<int>& arr, const std::string& stepName);

    void beginAuxPhase(std::vector<TableRow> initialRows, const std::string& stepName);
    void onAuxEvent(const std::vector<int>& mainArr, AuxEvent event, int srcIdx, int row, int pos, const std::string& stepName);
    void onCountEvent(AuxEvent event, const CountEventData& data, const std::string& stepName);

    void endAuxPhase(const std::vector<int>& arr, const std::string& stepName);

    void beginTreePhase(const std::string& stepName);
    void onTreeEvent(AuxEvent event, const TreeEventData& data, const std::string& stepName);
    void endTreePhase(const std::vector<int>& arr, const std::string& stepName);
};
