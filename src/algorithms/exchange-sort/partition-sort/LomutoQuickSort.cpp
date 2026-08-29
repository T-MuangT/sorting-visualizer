#include "LomutoQuickSort.hpp"
#include <algorithm>

namespace {
int partitionLomuto(std::vector<int>& arr, int low, int high, SortCallback notify) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (notify) notify(SortEvent::Compare, j, high, "Lomuto: Compare with Pivot");
        if (arr[j] <= pivot) {
            ++i;
            if (i != j) {
                std::swap(arr[i], arr[j]);
                if (notify) notify(SortEvent::Swap, i, j, "Lomuto: Swap Small Element");
            }
        }
    }
    
    if (i + 1 != high) {
        std::swap(arr[i + 1], arr[high]);
        if (notify) notify(SortEvent::Swap, i + 1, high, "Lomuto: Place Pivot");
    }
    return i + 1;
}

void lomutoQuickSortRecursive(std::vector<int>& arr, int low, int high, SortCallback notify) {
    if (low < high) {
        int pIdx = partitionLomuto(arr, low, high, notify);
        lomutoQuickSortRecursive(arr, low, pIdx - 1, notify);
        lomutoQuickSortRecursive(arr, pIdx + 1, high, notify);
    }
}
} // anonymous namespace

void lomutoQuickSort(std::vector<int>& arr, SortCallback notify) {
    if (!arr.empty()) {
        lomutoQuickSortRecursive(arr, 0, static_cast<int>(arr.size()) - 1, notify);
    }
}