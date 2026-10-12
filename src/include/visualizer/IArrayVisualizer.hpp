#pragma once

#include <vector>
#include <string>

#include "../Types.hpp"
#include "../AuxTypes.hpp"
#include "../SortStats.hpp"
#include "../algorithms/PartitionArray.hpp"

class IArrayVisualizer {
public:
    virtual ~IArrayVisualizer() = default;

    // Core contract required by all array-only visualizer backends
    virtual void renderFrame(
        const std::vector<int>& arr,
        SortEvent event,
        int idx1,
        int idx2,
        const std::string& stepName,
        const SortStats& stats) = 0;

    // Render an auxiliary array in a separate frame.
    virtual void renderAuxFrame(
        const std::vector<int>& arr,
        AuxEvent event,
        int highlightedIdx,
        const std::string& label,
        const std::string& stepName,
        const SortStats& stats) = 0;
};