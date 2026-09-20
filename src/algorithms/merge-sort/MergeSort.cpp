#include "MergeSort.hpp"
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

namespace{
std::string rangeLabel(int left, int right, int width = 0) {
    std::ostringstream oss;
    oss << "[" << std::setw(width) << left << "," << std::setw(width) << right << "]";
    return oss.str();
}

void mergeRange(std::vector<int>& arr, int left, int mid, int right, VisualizationSession& session) {
    std::vector<int> leftValues;
    std::vector<int> rightValues;

    leftValues.reserve(static_cast<size_t>(mid - left + 1));
    rightValues.reserve(static_cast<size_t>(right - mid));

    int numWidth = static_cast<int>(std::to_string(right).size());
    std::string leftLabel = rangeLabel(left, mid, numWidth);
    std::string rightLabel = rangeLabel(mid + 1, right, numWidth);

    session.beginAuxPhase(
        {
            {"Left  " + leftLabel, {}},
            {"Right " + rightLabel, {}}
        },
        "Merge Sort: Split " + rangeLabel(left, right, numWidth));

    for (int i = left; i <= mid; ++i) {
        leftValues.push_back(arr[static_cast<size_t>(i)]);
        session.onAuxEvent(arr, AuxEvent::PlaceInBucket, i, 0, static_cast<int>(leftValues.size()) - 1, "Merge Sort: Copy Left Half");
    }

    for (int i = mid + 1; i <= right; ++i) {
        rightValues.push_back(arr[static_cast<size_t>(i)]);
        session.onAuxEvent(arr, AuxEvent::PlaceInBucket, i, 1, static_cast<int>(rightValues.size()) - 1, "Merge Sort: Copy Right Half");
    }

    int leftIdx = 0;
    int rightIdx = 0;
    int writeIdx = left;

    while (leftIdx < static_cast<int>(leftValues.size()) &&
           rightIdx < static_cast<int>(rightValues.size())) {
        session.onAuxEvent(arr, AuxEvent::CompareInAux, writeIdx, 0, 0, "Merge Sort: Compare Left and Right Values");
        session.onAuxEvent(arr, AuxEvent::CompareInAux, writeIdx, 1, 0, "Merge Sort: Compare Left and Right Values");

        if (leftValues[static_cast<size_t>(leftIdx)] <= rightValues[static_cast<size_t>(rightIdx)]) {
            arr[static_cast<size_t>(writeIdx)] = leftValues[static_cast<size_t>(leftIdx)];
            session.onAuxEvent(arr, AuxEvent::FlushBucket, writeIdx, 0, 0, "Merge Sort: Write Left Value");
            ++leftIdx;
        } else {
            arr[static_cast<size_t>(writeIdx)] = rightValues[static_cast<size_t>(rightIdx)];
            session.onAuxEvent(arr, AuxEvent::FlushBucket, writeIdx, 1, 0, "Merge Sort: Write Right Value");
            ++rightIdx;
        }

        session.onArrayEvent(arr, SortEvent::Swap, writeIdx, writeIdx, "Merge Sort: Write Merged Array");
        ++writeIdx;
    }

    while (leftIdx < static_cast<int>(leftValues.size())) {
        arr[static_cast<size_t>(writeIdx)] = leftValues[static_cast<size_t>(leftIdx)];
        session.onAuxEvent(arr, AuxEvent::FlushBucket, writeIdx, 0, 0, "Merge Sort: Flush Left Half");
        session.onArrayEvent(arr, SortEvent::Swap, writeIdx, writeIdx, "Merge Sort: Write Remaining Left Value");
        ++leftIdx;
        ++writeIdx;
    }

    while (rightIdx < static_cast<int>(rightValues.size())) {
        arr[static_cast<size_t>(writeIdx)] = rightValues[static_cast<size_t>(rightIdx)];
        session.onAuxEvent(arr, AuxEvent::FlushBucket, writeIdx, 1, 0, "Merge Sort: Flush Right Half");
        session.onArrayEvent(arr, SortEvent::Swap, writeIdx, writeIdx, "Merge Sort: Write Remaining Right Value");
        ++rightIdx;
        ++writeIdx;
    }

    session.endAuxPhase(arr, "Merge Sort: Merged " + rangeLabel(left, right));
}

void mergeSortRecursive(std::vector<int>& arr, int left, int right, VisualizationSession& session) {
    if (left >= right) {
        return;
    }

    const int mid = left + (right - left) / 2;
    session.onArrayEvent(arr, SortEvent::Compare, left, right, "Merge Sort: Divide " + rangeLabel(left, right));

    mergeSortRecursive(arr, left, mid, session);
    mergeSortRecursive(arr, mid + 1, right, session);
    mergeRange(arr, left, mid, right, session);
}
}

void mergeSort(std::vector<int>& arr, VisualizationSession& session) {
    if (arr.empty()) {
        session.onArrayEvent(arr, SortEvent::Compare, -1, -1, "Merge Sort: Empty Array");
        return;
    }

    mergeSortRecursive(arr, 0, static_cast<int>(arr.size()) - 1, session);
    session.onArrayEvent(arr, SortEvent::Compare, -1, -1, "Merge Sort: Auxiliary Array Flush Complete");
}
