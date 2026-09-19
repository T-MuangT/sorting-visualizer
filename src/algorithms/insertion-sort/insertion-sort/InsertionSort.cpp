#include "InsertionSort.hpp"
#include <algorithm>
#include <string>

void insertionSort(std::vector<int>& arr, SortCallback notify) {
    int n = static_cast<int>(arr.size());
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0) {
            if (notify) {
                notify(SortEvent::Compare, j, i, "Insertion Sort: Compare");
            }

            if (arr[j] <= key) {
                break;
            }
            
            arr[j + 1] = arr[j];

            if (notify){
                notify(SortEvent::Shift, j, j + 1, "Insertion Sort: Shift " + std::to_string(key));
            }
            --j;
        }
        arr[j + 1] = key;

        if (notify) {
            notify(SortEvent::Insert, i, j + 1, "Insertion Sort: Insert" + std::to_string(key));
        }
    }
}