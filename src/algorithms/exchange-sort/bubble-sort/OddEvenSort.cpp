#include <string>

#include "../../../include/algorithms/PairwiseCompareSwap.hpp"
#include "OddEvenSort.hpp"

void oddEvenSort(std::vector<int>& arr, SortCallback notify) {
    int n = static_cast<int>(arr.size());
    bool isSorted = false;

    while (!isSorted) {
        isSorted = true;

        // Odd Phase
        for (int i = 1; i <= n - 2; i += 2) {
            if (notify) {
                notify(SortEvent::Compare, i, i + 1, "Odd-Even Sort: Odd Phase Compare " + std::to_string(arr[i]) + " and " + std::to_string(arr[i + 1]));
            }
            if (pairwiseCompareSwap(arr, i, i + 1)) {
                isSorted = false;
                if (notify) {
                    notify(SortEvent::Swap, i, i + 1, "Odd-Even Sort: Odd Phase Swap " + std::to_string(arr[i]) + " and " + std::to_string(arr[i + 1]));
                }
            }
        }

        // Even Phase
        for (int i = 0; i < n - 1; i += 2) {
            if (notify) {
                notify(SortEvent::Compare, i, i + 1, "Odd-Even Sort: Even Phase Compare " + std::to_string(arr[i]) + " and " + std::to_string(arr[i + 1]));
            }
            if (pairwiseCompareSwap(arr, i, i + 1)) {
                isSorted = false;
                if (notify) {
                    notify(SortEvent::Swap, i, i + 1, "Odd-Even Sort: Even Phase Swap " + std::to_string(arr[i]) + " and " + std::to_string(arr[i + 1]));
                }
            }
        }
    }
}