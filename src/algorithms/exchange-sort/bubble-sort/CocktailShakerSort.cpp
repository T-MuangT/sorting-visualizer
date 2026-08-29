#include "CocktailShakerSort.hpp"
#include <algorithm>
#include <string>

void cocktailShakerSort(std::vector<int>& arr, SortCallback notify) {
    int n = static_cast<int>(arr.size());
    bool swapped = true;
    int start = 0;
    int end = n - 1;

    while (swapped && start < end) {
        swapped = false;

        // Forward Pass (Left to Right)
        for (int i = start; i < end; ++i) {
            if (notify) notify(SortEvent::Compare, i, i + 1, "Forward Compare");
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                swapped = true;
                if (notify) notify(SortEvent::Swap, i, i + 1, "Forward Swap");
            }
        }

        if (!swapped) break;
        --end;
        swapped = false;

        // Backward Pass (Right to Left)
        for (int i = end - 1; i >= start; --i) {
            if (notify) notify(SortEvent::Compare, i, i + 1, "Backward Compare");
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                swapped = true;
                if (notify) notify(SortEvent::Swap, i, i + 1, "Backward Swap");
            }
        }

        ++start;
    }
}