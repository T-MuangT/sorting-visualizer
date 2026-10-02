#pragma once

#include <string>
#include <vector>

#include "../../src/include/visualizer/IArrayVisualizer.hpp"
#include "../../src/include/visualizer/ITableVisualizer.hpp"
#include "../../src/include/visualizer/IGraphVisualizer.hpp"

class NoopArrayVisualizer : public IArrayVisualizer {
public:
    void renderFrame(
        const std::vector<int>&,
        SortEvent,
        int,
        int,
        const std::string&,
        const SortStats&) override
    {}
};

class NoopTableVisualizer : public ITableVisualizer {
public:
    void renderFrame(
        const std::vector<TableRow>&,
        AuxEvent,
        const std::vector<TableCell>&,
        const std::string&,
        const SortStats&) override
    {}
};

class NoopGraphVisualizer : public IGraphVisualizer {
public:
    void renderFrame(
        const std::vector<TreeNode>&,
        AuxEvent,
        const std::vector<int>&,
        const std::string&,
        const SortStats&) override
    {}
};