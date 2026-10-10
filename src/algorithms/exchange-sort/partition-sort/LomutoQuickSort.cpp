#include <algorithm>
#include <string>

#include "../../../include/algorithms/PivotSelection.hpp"
#include "LomutoQuickSort.hpp"

namespace lomuto_quicksort_internal {
    int partitionLomuto(std::vector<int>& arr, int low, int high, SortCallback notify, PivotSelector selectPivot) {
        int pivotIndex = selectPivot(arr, low, high);

        if (pivotIndex != high) {
            std::swap(arr[pivotIndex], arr[high]);

            if (notify) {
                notify(SortEvent::Swap, pivotIndex, high, "Lomuto Quicksort: Move Pivot " + std::to_string(arr[pivotIndex]));
            }
        }

        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; ++j) {
            if (notify) {
                notify(SortEvent::Compare, j, high, "Lomuto Quicksort: Compare " + std::to_string(arr[j]) + " with Pivot " + std::to_string(pivot));
            }

            if (arr[j] <= pivot) {
                ++i;

                if (i != j) {
                    std::swap(arr[i], arr[j]);

                    if (notify) {
                        notify(SortEvent::Swap, i, j, "Lomuto Quicksort: Swap Small Element " + std::to_string(arr[i]));
                    }
                }
            }
        }

        if (i + 1 != high) {
            std::swap(arr[i + 1], arr[high]);

            if (notify) {
                notify(SortEvent::Swap, i + 1, high, "Lomuto Quicksort: Place Pivot " + std::to_string(pivot));
            }
        }

        return i + 1;
    }

    void lomutoQuickSortRecursive(std::vector<int>& arr, int low, int high, SortCallback notify, PivotSelector selectPivot) {
        if (low < high) {
            int pIdx = partitionLomuto(arr, low, high, notify, selectPivot);

            lomutoQuickSortRecursive(arr, low, pIdx - 1, notify, selectPivot);
            lomutoQuickSortRecursive(arr, pIdx + 1, high, notify, selectPivot);
        }
    }
}

void lomutoQuickSort(std::vector<int>& arr, SortCallback notify, PivotSelector selectPivot) {
    if (!arr.empty()) {
        lomuto_quicksort_internal::lomutoQuickSortRecursive(arr, 0, static_cast<int>(arr.size()) - 1, notify, selectPivot);
    }
}