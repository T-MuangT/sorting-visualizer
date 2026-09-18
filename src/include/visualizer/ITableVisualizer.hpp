#pragma once

#include <vector>
#include <string>
#include "../AuxTypes.hpp"
#include "../SortStats.hpp"

struct TableRow {
    std::string label;
    std::vector<int> values;
};

struct TableCell {
    int row;
    int pos;
};

class ITableVisualizer {
public:
    virtual ~ITableVisualizer() = default;

    virtual void renderFrame(
        const std::vector<TableRow>& rows,
        AuxEvent event,
        const std::vector<TableCell>& highlighted,
        const std::string& stepName,
        const SortStats& stats) = 0;
};