#include <algorithm>
#include <string>
#include <cassert>

#include "../../../include/algorithms/PivotSelection.hpp"
#include "HoareQuickSort.hpp"

namespace hoare_quicksort_internal {
    struct PreparedHoarePivot {
        int value;
        int index;
    };

    PreparedHoarePivot prepareHoarePivot(std::vector<int>& arr, int low, int high, SortCallback notify, PivotSelector selectPivot) {
        int pivotIndex = selectPivot(arr, low, high);

        assert(pivotIndex >= low && pivotIndex <= high && "PivotSelector returned out-of-range index");

        // Release-mode fallback for a broken selector.
        if (pivotIndex < low || pivotIndex > high) {
            pivotIndex = low + (high - low) / 2;
        }

        const int pivot = arr[pivotIndex];
        const int mid = low + (high - low) / 2;

        if (pivotIndex != mid) {
            std::swap(arr[pivotIndex], arr[mid]);

            if (notify) {
                notify(SortEvent::Swap, pivotIndex, mid, "Hoare Quicksort: Move Pivot " + std::to_string(pivot) + " to Middle");
            }

            pivotIndex = mid;
        }

        return {pivot, pivotIndex};
    }

    int partitionHoare(std::vector<int>& arr, int low, int high, SortCallback notify, PivotSelector selectPivot) {
        const PreparedHoarePivot selected = prepareHoarePivot(arr, low, high, notify, selectPivot);
        const int pivot = selected.value;
        const int pivotIndex = selected.index;

        int i = low - 1;
        int j = high + 1;

        while (true) {
            do {
                ++i;
                if (notify) notify(SortEvent::Compare, i, pivotIndex, "Hoare Quicksort: Scanning Left of " + std::to_string(pivot));
            } while (arr[i] < pivot);

            do {
                --j;
                if (notify) notify(SortEvent::Compare, j, pivotIndex, "Hoare Quicksort: Scanning Right of " + std::to_string(pivot));
            } while (arr[j] > pivot);

            if (i >= j) return j;

            std::swap(arr[i], arr[j]);
            if (notify) notify(SortEvent::Swap, i, j, "Hoare Quicksort: Swap Out-of-Order Pair " + std::to_string(arr[i]) + " and " + std::to_string(arr[j]));
        }
    }

    void hoareQuickSortRecursive(std::vector<int>& arr, int low, int high, SortCallback notify, PivotSelector selectPivot) {
        // Recursive range must always be valid.
        assert(low >= 0);
        assert(high < static_cast<int>(arr.size()));
        assert(low <= high);

        if (low < high) {
            int pIdx = partitionHoare(arr, low, high, notify, selectPivot);

            // Hoare partition must split the range into two
            // strictly smaller ranges.
            assert(low <= pIdx);
            assert(pIdx < high);

            hoareQuickSortRecursive(arr, low, pIdx, notify, selectPivot);
            hoareQuickSortRecursive(arr, pIdx + 1, high, notify, selectPivot);
        }
    }
}

void hoareQuickSort(std::vector<int>& arr, SortCallback notify, PivotSelector selectPivot) {
    if (!arr.empty()) {
        hoare_quicksort_internal::hoareQuickSortRecursive(arr, 0, static_cast<int>(arr.size()) - 1, notify, selectPivot);
    }
}