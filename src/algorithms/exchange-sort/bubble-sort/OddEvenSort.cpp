#include "OddEvenSort.hpp"
#include <algorithm>
#include <string>

void oddEvenSort(std::vector<int>& arr, SortCallback notify) {
    int n = static_cast<int>(arr.size());
    bool isSorted = false;

    while (!isSorted) {
        isSorted = true;

        // Odd Phase
        for (int i = 1; i <= n - 2; i += 2) {
            if (notify) {
                notify(SortEvent::Compare, i, i + 1, "Odd Phase Compare");
            }
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                isSorted = false;
                if (notify) {
                    notify(SortEvent::Swap, i, i + 1, "Odd Phase Swap");
                }
            }
        }

        // Even Phase
        for (int i = 0; i < n - 1; i += 2) {
            if (notify) {
                notify(SortEvent::Compare, i, i + 1, "Even Phase Compare");
            }
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                isSorted = false;
                if (notify) {
                    notify(SortEvent::Swap, i, i + 1, "Even Phase Swap");
                }
            }
        }
    }
}