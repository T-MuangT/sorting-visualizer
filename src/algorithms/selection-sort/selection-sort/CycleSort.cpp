#include "CycleSort.hpp"
#include <algorithm>

void cycleSort(std::vector<int>& arr, SortCallback notify) {
    int n = static_cast<int>(arr.size());

    for (int cycleStart = 0; cycleStart <= n - 2; ++cycleStart) {
        int item = arr[cycleStart];

        // Find the position where the item belongs
        int pos = cycleStart;
        for (int i = cycleStart + 1; i < n; ++i) {
            if (notify) notify(SortEvent::Compare, i, cycleStart, "Cycle Sort: Find position");
            if (arr[i] < item) {
                pos++;
            }
        }

        // If the item is already in place, skip
        if (pos == cycleStart) {
            continue;
        }

        // Skip duplicates to avoid infinite loops or incorrect placement
        while (item == arr[pos]) {
            pos += 1;
        }

        // Put the item to its correct position
        if (pos != cycleStart) {
            std::swap(item, arr[pos]);
            if (notify) notify(SortEvent::Swap, pos, cycleStart, "Cycle Sort: Place item");
        }

        // Rotate the rest of the cycle
        while (pos != cycleStart) {
            pos = cycleStart;
            for (int i = cycleStart + 1; i < n; ++i) {
                if (notify) notify(SortEvent::Compare, i, cycleStart, "Cycle Sort: Rotate cycle");
                if (arr[i] < item) {
                    pos++;
                }
            }

            while (item == arr[pos]) {
                pos += 1;
            }

            if (item != arr[pos]) {
                std::swap(item, arr[pos]);
                if (notify) notify(SortEvent::Swap, pos, cycleStart, "Cycle Sort: Rotate swap");
            }
        }
    }
}