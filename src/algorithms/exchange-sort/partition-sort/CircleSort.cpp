#include <string>

#include "../../../include/algorithms/PairwiseCompareSwap.hpp"
#include "../../../include/algorithms/ArraySplitRange.hpp"
#include "CircleSort.hpp"

static bool circleSortRecursive(std::vector<int>& arr, const ArraySplitRange& range, SortCallback notify) {
    bool swapped = false;
    if (!isValid(range) || isSingleton(range)) return false;

    int left = range.low;
    int right = range.high;

    while (left < right) {
        if (notify) {
            notify(SortEvent::Compare, left, right, "Circle Sort: Compare " + std::to_string(arr[left]) + " and " + std::to_string(arr[right]));
        }
        if (pairwiseCompareSwap(arr, left, right)) {
            swapped = true;
            if (notify) {
                notify(SortEvent::Swap, left, right, "Circle Sort: Swap " + std::to_string(arr[left]) + " and " + std::to_string(arr[right]));
            }
        }
        left++;
        right--;
    }

    // Special case for odd number of elements
    if (left == right) {
        if (notify) {
            notify(SortEvent::Compare, left, right + 1, "Circle Sort: Midpoint Compare " + std::to_string(arr[left]) + " and " + std::to_string(arr[right + 1]));
        }
        if (pairwiseCompareSwap(arr, left, right + 1)) {
            swapped = true;
            if (notify) {
                notify(SortEvent::Swap, left, right + 1, "Circle Sort: Midpoint Swap " + std::to_string(arr[left]) + " and " + std::to_string(arr[right + 1]));
            }
        }
    }

    int mid = midpoint(range);
    ArraySplitRange leftRange{range.low, mid};
    ArraySplitRange rightRange{mid + 1, range.high};
    bool leftSwapped = circleSortRecursive(arr, leftRange, notify);
    bool rightSwapped = circleSortRecursive(arr, rightRange, notify);

    return swapped || leftSwapped || rightSwapped;
}

void circleSort(std::vector<int>& arr, SortCallback notify) {
    if (arr.empty()) return;
    ArraySplitRange range{
        0,
        static_cast<int>(arr.size()) - 1
    };

    while (circleSortRecursive(arr, range, notify)) {
        // Repeat until no swaps occur
    }
}