#include <string>

#include "../../../include/algorithms/PairwiseCompareSwap.hpp"
#include "CocktailShakerSort.hpp"

void cocktailShakerSort(std::vector<int>& arr, SortCallback notify) {
    int n = static_cast<int>(arr.size());
    bool swapped = true;
    int start = 0;
    int end = n - 1;

    while (swapped && start < end) {
        swapped = false;

        // Forward Pass (Left to Right)
        for (int i = start; i < end; ++i) {
            if (notify) notify(SortEvent::Compare, i, i + 1, "Cocktail Shaker Sort: Forward Compare " + std::to_string(arr[i]) + " and " + std::to_string(arr[i + 1]));
            if (pairwiseCompareSwap(arr, i, i + 1)) {
                swapped = true;
                if (notify) notify(SortEvent::Swap, i, i + 1, "Cocktail Shaker Sort: Forward Swap " + std::to_string(arr[i]) + " and " + std::to_string(arr[i + 1]));
            }
        }

        if (!swapped) break;
        --end;
        swapped = false;

        // Backward Pass (Right to Left)
        for (int i = end - 1; i >= start; --i) {
            if (notify) notify(SortEvent::Compare, i, i + 1, "Cocktail Shaker Sort: Backward Compare " + std::to_string(arr[i]) + " and " + std::to_string(arr[i + 1]));
            if (pairwiseCompareSwap(arr, i, i + 1)) {
                swapped = true;
                if (notify) notify(SortEvent::Swap, i, i + 1, "Cocktail Shaker Sort: Backward Swap " + std::to_string(arr[i]) + " and " + std::to_string(arr[i + 1]));
            }
        }

        ++start;
    }
}