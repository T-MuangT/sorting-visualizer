#include "StableQuickSort.hpp"

namespace {
void stableQuickSortRecursive(std::vector<int>& arr, int startIdx, SortCallback notify) {
    if (arr.size() <= 1) return;

    int pivot = arr[0];
    std::vector<int> left;
    std::vector<int> middle;
    std::vector<int> right;

    for (size_t i = 0; i < arr.size(); ++i) {
        int globalIdx = startIdx + static_cast<int>(i);
        if (notify) notify(SortEvent::Compare, globalIdx, startIdx, "Stable Quick: Partition Compare");

        if (arr[i] < pivot) {
            left.push_back(arr[i]);
        } else if (arr[i] == pivot) {
            middle.push_back(arr[i]);
        } else {
            right.push_back(arr[i]);
        }
    }

    stableQuickSortRecursive(left, startIdx, notify);
    stableQuickSortRecursive(right, startIdx + static_cast<int>(left.size() + middle.size()), notify);

    // Reconstruct input partition and report updates
    size_t idx = 0;
    for (int val : left) {
        arr[idx] = val;
        if (notify) notify(SortEvent::Swap, startIdx + static_cast<int>(idx), startIdx + static_cast<int>(idx), "Stable Quick: Write Left");
        ++idx;
    }
    for (int val : middle) {
        arr[idx] = val;
        if (notify) notify(SortEvent::Swap, startIdx + static_cast<int>(idx), startIdx + static_cast<int>(idx), "Stable Quick: Write Pivot");
        ++idx;
    }
    for (int val : right) {
        arr[idx] = val;
        if (notify) notify(SortEvent::Swap, startIdx + static_cast<int>(idx), startIdx + static_cast<int>(idx), "Stable Quick: Write Right");
        ++idx;
    }
}
} // anonymous namespace

void stableQuickSort(std::vector<int>& arr, SortCallback notify) {
    if (!arr.empty()) {
        stableQuickSortRecursive(arr, 0, notify);
    }
}