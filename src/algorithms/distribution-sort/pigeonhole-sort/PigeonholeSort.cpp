#include "PigeonholeSort.hpp"

#include <algorithm>
#include <string>

void pigeonholeSort(std::vector<int>& arr, VisualizationSession& session) {
    if (arr.empty()) {
        session.onArrayEvent(arr, SortEvent::Compare, -1, -1, "Pigeonhole Sort: Empty array");
        return;
    }

    session.onArrayEvent(arr, SortEvent::Compare, 0, 0, "Pigeonhole Sort: Scan Minimum and Maximum");

    const auto [minIt, maxIt] = std::minmax_element(arr.begin(), arr.end());
    const int minValue = *minIt;
    const int maxValue = *maxIt;
    const int bucketCount = maxValue - minValue + 1;

    std::vector<TableRow> rows;
    rows.reserve(static_cast<size_t>(bucketCount));
    for (int value = minValue; value <= maxValue; ++value) {
        rows.push_back({"Bucket " + std::to_string(value), {}});
    }

    std::vector<std::vector<int>> buckets(static_cast<size_t>(bucketCount));
    session.beginAuxPhase(std::move(rows), "Pigeonhole Sort: Create Buckets");

    for (int i = 0; i < static_cast<int>(arr.size()); ++i) {
        const int row = arr[static_cast<size_t>(i)] - minValue;
        auto& bucket = buckets[static_cast<size_t>(row)];
        bucket.push_back(arr[static_cast<size_t>(i)]);

        session.onAuxEvent(
            arr,
            AuxEvent::PlaceInBucket,
            i,
            row,
            static_cast<int>(bucket.size()) - 1,
            "Pigeonhole Sort: Place " + std::to_string(arr[static_cast<size_t>(i)]));
    }

    int writeIdx = 0;
    for (int row = 0; row < bucketCount; ++row) {
        auto& bucket = buckets[static_cast<size_t>(row)];
        while (!bucket.empty()) {
            arr[static_cast<size_t>(writeIdx)] = bucket.front();
            bucket.erase(bucket.begin());

            session.onAuxEvent(
                arr,
                AuxEvent::FlushBucket,
                writeIdx,
                row,
                0,
                "Pigeonhole Sort: Flush Bucket " + std::to_string(row + minValue));

            session.onArrayEvent(
                arr,
                SortEvent::Swap,
                writeIdx,
                writeIdx,
                "Pigeonhole Sort: Write Back " + std::to_string(arr[static_cast<size_t>(writeIdx)]));

            ++writeIdx;
        }
    }

    session.endAuxPhase(arr, "Pigeonhole Sort: Auxiliary Array Flush Complete");
}
