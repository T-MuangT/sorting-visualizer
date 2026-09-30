#include <algorithm>
#include <string>
#include <vector>

#include "../../../include/algorithms/CountEventData.hpp"
#include "CountingSort.hpp"

void countingSort(std::vector<int>& arr, VisualizationSession& session) {
    if (arr.empty()) {
        session.onArrayEvent(arr, SortEvent::Compare, -1, -1, "Counting Sort: Empty Array");
        return;
    }

    // Find the range of values.
    session.onArrayEvent(arr, SortEvent::Compare, 0, 0, "Counting Sort: Scan Values");

    const auto [minIt, maxIt] = std::minmax_element(arr.begin(), arr.end());
    const int minValue = *minIt;
    const int maxValue = *maxIt;
    const int countRange = maxValue - minValue + 1;

    // Create the count table.
    std::vector<TableRow> rows;
    rows.reserve(static_cast<size_t>(countRange) + 1);

    for (int value = minValue; value <= maxValue; ++value) {
        rows.push_back({"Count " + std::to_string(value), {0}});
    }

    rows.push_back({"Output", std::vector<int>(arr.size())});
    const int outputRow = static_cast<int>(rows.size()) - 1;

    std::vector<int> counts(static_cast<size_t>(countRange), 0);

    session.beginAuxPhase(std::move(rows), "Counting Sort: Create Count Array");

    // Count the frequency of each value.
    for (int i = 0; i < static_cast<int>(arr.size()); ++i) {
        const int value = arr[static_cast<size_t>(i)];
        const int row = value - minValue;

        ++counts[static_cast<size_t>(row)];

        session.onCountEvent(AuxEvent::IncrementCount, CountEventData{.srcIdx = i, .countRow = row, .value = counts[static_cast<size_t>(row)]}, "Counting Sort: Count " + std::to_string(value));
    }

    // Convert frequencies into cumulative counts.
    for (int row = 1; row < countRange; ++row) {
        counts[static_cast<size_t>(row)] += counts[static_cast<size_t>(row - 1)];

        session.onCountEvent(AuxEvent::AccumulateCount, CountEventData{.countRow = row, .value = counts[static_cast<size_t>(row)]}, "Counting Sort: Cumulative Count " + std::to_string(row + minValue));
    }

    // Place elements into their final positions.
    // Traversing from right to left makes the sort stable.
    std::vector<int> output(arr.size());

    for (int i = static_cast<int>(arr.size()) - 1; i >= 0; --i) {
        const int value = arr[static_cast<size_t>(i)];
        const int row = value - minValue;

        const int position =
            counts[static_cast<size_t>(row)] - 1;

        output[static_cast<size_t>(position)] = value;
        --counts[static_cast<size_t>(row)];

        session.onCountEvent(AuxEvent::PlaceCountOutput, CountEventData{.srcIdx = i, .countRow = row, .outputRow = outputRow, .outputPos = position, .value = value}, "Counting Sort: Place " + std::to_string(value) + " at Position " + std::to_string(position));
    }

    // Copy the sorted output back into the input array.
    for (int i = 0; i < static_cast<int>(arr.size()); ++i) {
        arr[static_cast<size_t>(i)] = output[static_cast<size_t>(i)];

        session.onArrayEvent(arr, SortEvent::Swap, i, i, "Counting Sort: Write Back " + std::to_string(arr[static_cast<size_t>(i)]));
    }

    session.endAuxPhase(arr, "Counting Sort: Auxiliary Array Flush Complete");
}