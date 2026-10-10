#pragma once

#include <vector>

#include "../../../include/Types.hpp"
#include "../../../include/algorithms/PivotSelection.hpp"

void hoareQuickSort(std::vector<int>& arr, SortCallback notify, PivotSelector selectPivot);