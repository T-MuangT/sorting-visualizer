#include <string>

#include "../../../include/algorithms/PairwiseCompareSwap.hpp"
#include "OptimizedBubbleSort.hpp"

void optimizedBubbleSort(std::vector<int>& arr, SortCallback notify) {
    int end = static_cast<int>(arr.size()) - 1;

    while (end > 0) {
        int newEnd = 0;

        for (int i = 0; i < end; ++i) {
            if (notify) {
                notify(SortEvent::Compare, i, i + 1, "Bubble Sort with Early Cutoff: Compare " + std::to_string(arr[i]) + " and " + std::to_string(arr[i + 1]));
            }

            if (pairwiseCompareSwap(arr, i, i + 1)) {
                newEnd = i;

                if (notify) {
                    notify(SortEvent::Swap, i, i + 1, "Bubble Sort with Early Cutoff: Swap " + std::to_string(arr[i]) + " and " + std::to_string(arr[i + 1]));
                }
            }
        }
        
        end = newEnd;
    }
}