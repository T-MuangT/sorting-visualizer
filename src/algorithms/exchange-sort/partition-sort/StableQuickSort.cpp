#include <string>

#include "StableQuickSort.hpp"

namespace stable_quicksort_internal {
void stableQuickSortRecursive(std::vector<int>& arr, int startIdx, VisualizationSession& session) {
    if (arr.size() <= 1) {
        return;
    }

    session.onArrayEvent(arr, SortEvent::Compare, -1, -1, "Stabel Quicksort: Original Array");

    const int pivot = arr[0];
    std::vector<int> left;
    std::vector<int> middle;
    std::vector<int> right;

    const std::string stepName = "Stable Quicksort: Partition " + std::to_string(pivot);

    // Prepare three auxiliary partition arrays: Left, Pivot, Right
    session.beginPartitionPhase(
        {
            {"Left    (Fewer)", {}},
            {"Pivot   (Equal)", {}},
            {"Right (Greater)", {}}
        },
        stepName);

    for (size_t i = 0; i < arr.size(); ++i) {
        PartitionEventData data{};
        data.srcIdx = static_cast<int>(i);
        data.startIdx = 0;
        data.endIdx = static_cast<int>(arr.size()) - 1;
        data.pivotValue = pivot;
        data.leftRow = 0;
        data.middleRow = 1;
        data.rightRow = 2;
        data.value = arr[i];

        if (arr[i] < pivot) {
            data.leftPos = static_cast<int>(left.size());
            session.onPartitionEvent(arr, data, stepName);
            left.push_back(arr[i]);
        } else if (arr[i] == pivot) {
            data.middlePos = static_cast<int>(middle.size());
            session.onPartitionEvent(arr, data, stepName);
            middle.push_back(arr[i]);
        } else {
            data.rightPos = static_cast<int>(right.size());
            session.onPartitionEvent(arr, data, stepName);
            right.push_back(arr[i]);
        }
    }

    // Recursively sort left and right partitions (they are separate vectors)
    stableQuickSortRecursive(left, startIdx, session);
    stableQuickSortRecursive(right, startIdx + static_cast<int>(left.size() + middle.size()), session);

    // Reconstruct the original array segment from left, middle, right
    size_t idx = 0;
    for (int val : left) {
        arr[idx] = val;
        session.onArrayEvent(arr, SortEvent::Swap, static_cast<int>(idx), static_cast<int>(idx), "Stable Quicksort: Write Left " + std::to_string(arr[idx]));
        ++idx;
    }
    for (int val : middle) {
        arr[idx] = val;
        session.onArrayEvent(arr, SortEvent::Swap, static_cast<int>(idx), static_cast<int>(idx), "Stable Quicksort: Write Pivot " + std::to_string(arr[idx]));
        ++idx;
    }
    for (int val : right) {
        arr[idx] = val;
        session.onArrayEvent(arr, SortEvent::Swap, static_cast<int>(idx), static_cast<int>(idx), "Stable Quicksort: Write Right " + std::to_string(arr[idx]));
        ++idx;
    }

    session.endPartitionPhase(arr, "Stable Quicksort: Reconstructed Array");
}
} // anonymous namespace

void stableQuickSort(std::vector<int>& arr, VisualizationSession& session) {
    if (!arr.empty()) {
        stable_quicksort_internal::stableQuickSortRecursive(arr, 0, session);
    }
}
