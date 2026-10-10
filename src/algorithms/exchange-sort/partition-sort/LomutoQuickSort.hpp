#pragma once

#include <vector>

#include "../../../include/Types.hpp"
#include "../../../include/algorithms/PivotSelection.hpp"

void lomutoQuickSort(std::vector<int>& arr, SortCallback notify, PivotSelector selectPivot);