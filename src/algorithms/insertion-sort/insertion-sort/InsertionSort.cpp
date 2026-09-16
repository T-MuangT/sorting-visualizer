#include "InsertionSort.hpp"
#include <algorithm>
#include <string>

void insertionSort(std::vector<int>& arr, SortCallback notify) {
    int n = static_cast<int>(arr.size());
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            if (notify) notify(SortEvent::Swap, j, j + 1, "Insertion Swap " + std::to_string(key));
            --j;
        }
        arr[j + 1] = key;
    }
}