#include "BinaryInsertionSort.hpp"
#include <algorithm>
#include <string>

void binaryInsertionSort(std::vector<int>& arr, SortCallback notify) {
    int n = static_cast<int>(arr.size());
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int left = 0;
        int right = i - 1;

        // Perform binary search to find the correct position for key
        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (notify) {
                notify(SortEvent::Compare, mid, i, "Binary Insertion Sort: Compare");
            }

            if (arr[mid] > key) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        // Shift elements to make space for key
        for (int j = i - 1; j >= left; --j) {
            arr[j + 1] = arr[j];
            if (notify) notify(SortEvent::Shift, j, j + 1, "Binary Insertion Sort: Shift " + std::to_string(key));
        }
        arr[left] = key;

        if (notify) {
            notify(SortEvent::Insert, i, left, "Binary Insertion Sort: Insert " + std::to_string(key));
        }
    }
}