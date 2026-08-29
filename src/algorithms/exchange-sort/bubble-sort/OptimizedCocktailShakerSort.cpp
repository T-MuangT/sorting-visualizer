#include "OptimizedCocktailShakerSort.hpp"
#include <algorithm>
#include <string>

void optimizedCocktailShakerSort(std::vector<int>& arr, SortCallback notify) {
    int start = 0;
    int end = static_cast<int>(arr.size()) - 1;

    while (start < end) {
        int newEnd = start;

        // Forward Pass
        for (int i = start; i < end; ++i) {
            if (notify) notify(SortEvent::Compare, i, i + 1, "Forward Compare");
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                newEnd = i;
                if (notify) notify(SortEvent::Swap, i, i + 1, "Forward Swap");
            }
        }
        end = newEnd;
        if (start >= end) break;

        int newStart = end;

        // Backward Pass
        for (int i = end - 1; i >= start; --i) {
            if (notify) notify(SortEvent::Compare, i, i + 1, "Backward Compare");
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                newStart = i;
                if (notify) notify(SortEvent::Swap, i, i + 1, "Backward Swap");
            }
        }
        start = newStart + 1;
    }
}