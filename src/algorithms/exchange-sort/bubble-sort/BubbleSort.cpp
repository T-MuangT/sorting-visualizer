#include "BubbleSort.hpp"
#include <algorithm>
#include <string>

void bubbleSort(std::vector<int>& arr, SortCallback notify) {
    int n = static_cast<int>(arr.size());
    bool swapped = true;

    for (int pass = 0; pass < n - 1 && swapped; ++pass) {
        swapped = false;
        for (int i = 0; i < n - pass - 1; ++i) {
            if (notify) notify(SortEvent::Compare, i, i + 1, "Pass " + std::to_string(pass + 1));

            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                swapped = true;
                if (notify) notify(SortEvent::Swap, i, i + 1, "Swap Pass " + std::to_string(pass + 1));
            }
        }
    }
}