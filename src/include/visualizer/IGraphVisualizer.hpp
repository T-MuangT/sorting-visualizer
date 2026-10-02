#pragma once

#include <vector>
#include <string>

#include "../AuxTypes.hpp"
#include "../SortStats.hpp"

struct TreeNode {
    int value;
    int parent;
    int left;
    int right;
};

class IGraphVisualizer {
public:
    virtual ~IGraphVisualizer() = default;

    virtual void renderFrame(
        const std::vector<TreeNode>& nodes,
        AuxEvent event,
        const std::vector<int>& highlighted,
        const std::string& stepName,
        const SortStats& stats) = 0;
};