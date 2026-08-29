#pragma once

#include <vector>
#include <string>
#include "../Types.hpp"
#include "../SortStats.hpp"

class IVisualizer {
public:
    virtual ~IVisualizer() = default;

    // Core contract required by all visualizer backends
    virtual void renderFrame(
        const std::vector<int>& arr,
        SortEvent event,
        int idx1,
        int idx2,
        const std::string& stepName,
        const SortStats& stats) = 0;
};