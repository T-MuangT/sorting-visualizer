#include "SequentialCombSort.hpp"
#include <algorithm>
#include <string>

void sequentialCombSort(std::vector<int>& arr, SortCallback notify) {
    int n = static_cast<int>(arr.size());
    int gap = n;
    bool swapped = true;
    const double shrink = 1.3;

    while (gap > 1 || swapped) {
        gap = static_cast<int>(gap / shrink);
        if (gap < 1) gap = 1;

        swapped = false;

        for (int i = 0; i < n - gap; ++i) {
            if (notify) notify(SortEvent::Compare, i, i + gap, "Gap " + std::to_string(gap));

            if (arr[i] > arr[i + gap]) {
                std::swap(arr[i], arr[i + gap]);
                swapped = true;
                if (notify) notify(SortEvent::Swap, i, i + gap, "Gap Swap");
            }
        }
    }
}