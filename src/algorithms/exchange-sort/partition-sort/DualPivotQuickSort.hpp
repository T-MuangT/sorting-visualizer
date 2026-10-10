#pragma once

#include <vector>

#include "../../../include/Types.hpp"
#include "../../../include/algorithms/PivotSelection.hpp"

void dualPivotQuickSort(std::vector<int>& arr, SortCallback notify, DualPivotSelector selectPivots);