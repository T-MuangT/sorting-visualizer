#include <string>

#include "../../../include/algorithms/PairwiseCompareSwap.hpp"
#include "OptimizedCocktailShakerSort.hpp"

void optimizedCocktailShakerSort(std::vector<int>& arr, SortCallback notify) {
    int start = 0;
    int end = static_cast<int>(arr.size()) - 1;

    while (start < end) {
        int newEnd = start;

        // Forward Pass
        for (int i = start; i < end; ++i) {
            if (notify) notify(SortEvent::Compare, i, i + 1, "Cocktail Shaker Sort with Early Cutoff: Forward Compare " + std::to_string(arr[i]) + " and " + std::to_string(arr[i + 1]));
            if (pairwiseCompareSwap(arr, i, i + 1)) {
                newEnd = i;
                if (notify) notify(SortEvent::Swap, i, i + 1, "Cocktail Shaker Sort with Early Cutoff: Forward Swap " + std::to_string(arr[i]) + " and " + std::to_string(arr[i + 1]));
            }
        }
        end = newEnd;
        if (start >= end) break;

        int newStart = end;

        // Backward Pass
        for (int i = end - 1; i >= start; --i) {
            if (notify) notify(SortEvent::Compare, i, i + 1, "Cocktail Shaker Sort with Early Cutoff: Backward Compare " + std::to_string(arr[i]) + " and " + std::to_string(arr[i + 1]));
            if (pairwiseCompareSwap(arr, i, i + 1)) {
                newStart = i;
                if (notify) notify(SortEvent::Swap, i, i + 1, "Cocktail Shaker Sort with Early Cutoff: Backward Swap " + std::to_string(arr[i]) + " and " + std::to_string(arr[i + 1]));
            }
        }
        start = newStart + 1;
    }
}