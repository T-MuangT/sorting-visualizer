#include "DoubleSelectionSort.hpp"
#include <algorithm>

void doubleSelectionSort(std::vector<int>& arr, SortCallback notify) {
    int low = 0;
    int high = static_cast<int>(arr.size()) - 1;

    while (low < high) {
        int minIdx = low;
        int maxIdx = high;

        // Ensure initial bounds check order
        if (arr[minIdx] > arr[maxIdx]) {
            std::swap(arr[minIdx], arr[maxIdx]);
            if (notify) notify(SortEvent::Swap, minIdx, maxIdx, "Double Selection: Bounds Swap");
        }

        for (int j = low + 1; j < high; ++j) {
            if (notify) notify(SortEvent::Compare, j, minIdx, "Double Selection: Compare Min");
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
            if (notify) notify(SortEvent::Compare, j, maxIdx, "Double Selection: Compare Max");
            if (arr[j] > arr[maxIdx]) {
                maxIdx = j;
            }
        }

        if (minIdx != low) {
            std::swap(arr[low], arr[minIdx]);
            if (notify) notify(SortEvent::Swap, low, minIdx, "Double Selection: Swap Min to Left");
        }

        if (maxIdx != high) {
            std::swap(arr[high], arr[maxIdx]);
            if (notify) notify(SortEvent::Swap, high, maxIdx, "Double Selection: Swap Max to Right");
        }

        ++low;
        --high;
    }
}