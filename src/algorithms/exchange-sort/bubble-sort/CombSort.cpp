#include <string>

#include "../../../include/algorithms/PairwiseCompareSwap.hpp"
#include "CombSort.hpp"

void combSort(std::vector<int>& arr, SortCallback notify) {
    int n = static_cast<int>(arr.size());
    int gap = n;
    bool swapped = true;
    const double shrink = 1.3;

    while (gap > 1 || swapped) {
        gap = static_cast<int>(gap / shrink);
        if (gap < 1) gap = 1;

        swapped = false;

        for (int i = 0; i < n - gap; ++i) {
            if (notify) notify(SortEvent::Compare, i, i + gap, "Comb Sort: Gap Compare " + std::to_string(gap) + " between " + std::to_string(arr[i]) + " and " + std::to_string(arr[i + gap]));

            if (pairwiseCompareSwap(arr, i, i + gap)) {
                swapped = true;
                if (notify) notify(SortEvent::Swap, i, i + gap, "Comb Sort: Gap Swap " + std::to_string(arr[i]) + " and " + std::to_string(arr[i + gap]));
            }
        }
    }
}