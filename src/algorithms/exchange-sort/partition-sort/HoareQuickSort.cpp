#include "HoareQuickSort.hpp"
#include <algorithm>

namespace {
int partitionHoare(std::vector<int>& arr, int low, int high, SortCallback notify) {
    int pivot = arr[low + (high - low) / 2];
    int i = low - 1;
    int j = high + 1;

    while (true) {
        do {
            ++i;
            if (notify) notify(SortEvent::Compare, i, low + (high - low) / 2, "Hoare Quicksort: Scanning Left");
        } while (arr[i] < pivot);

        do {
            --j;
            if (notify) notify(SortEvent::Compare, j, low + (high - low) / 2, "Hoare Quicksort: Scanning Right");
        } while (arr[j] > pivot);

        if (i >= j) return j;

        std::swap(arr[i], arr[j]);
        if (notify) notify(SortEvent::Swap, i, j, "Hoare Quicksort: Swap Out-of-Order Pair");
    }
}

void hoareQuickSortRecursive(std::vector<int>& arr, int low, int high, SortCallback notify) {
    if (low < high) {
        int pIdx = partitionHoare(arr, low, high, notify);
        hoareQuickSortRecursive(arr, low, pIdx, notify);
        hoareQuickSortRecursive(arr, pIdx + 1, high, notify);
    }
}
} // anonymous namespace

void hoareQuickSort(std::vector<int>& arr, SortCallback notify) {
    if (!arr.empty()) {
        hoareQuickSortRecursive(arr, 0, static_cast<int>(arr.size()) - 1, notify);
    }
}