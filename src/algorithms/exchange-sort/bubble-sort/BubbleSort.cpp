#include <string>

#include "../../../include/algorithms/PairwiseCompareSwap.hpp"
#include "BubbleSort.hpp"

void bubbleSort(std::vector<int>& arr, SortCallback notify) {
    int n = static_cast<int>(arr.size());
    bool swapped = true;

    for (int pass = 0; pass < n - 1 && swapped; ++pass) {
        swapped = false;

        for (int i = 0; i < n - pass - 1; ++i) {
            const std::string compareStep = "Bubble Sort: Compare " + std::to_string(arr[i]) + " and " + std::to_string(arr[i + 1]);

            if (notify) {
                notify(SortEvent::Compare, i, i + 1, compareStep);
            }

            if (pairwiseCompareSwap(arr, i, i + 1)) {
                swapped = true;

                if (notify) {
                    notify(SortEvent::Swap, i, i + 1, "Bubble Sort: Swap " + std::to_string(arr[i]) + " and " + std::to_string(arr[i + 1]));
                }
            }
        }
    }
}