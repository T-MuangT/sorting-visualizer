#include "SelectionSort.hpp"
#include <algorithm>

void selectionSort(std::vector<int>& arr, SortCallback notify) {
    int n = static_cast<int>(arr.size());
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (notify) notify(SortEvent::Compare, j, minIdx, "Selection: Compare elements");
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            std::swap(arr[i], arr[minIdx]);
            if (notify) notify(SortEvent::Swap, i, minIdx, "Selection: Swap minimum to front");
        }
    }
}