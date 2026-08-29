#include "CircleSort.hpp"
#include <algorithm>
#include <string>

static bool circleSortRecursive(std::vector<int>& arr, int low, int high, SortCallback notify) {
    bool swapped = false;
    if (low >= high) return false;

    int left = low;
    int right = high;

    while (left < right) {
        if (notify) {
            notify(SortEvent::Compare, left, right, "Circle Compare");
        }
        if (arr[left] > arr[right]) {
            std::swap(arr[left], arr[right]);
            swapped = true;
            if (notify) {
                notify(SortEvent::Swap, left, right, "Circle Swap");
            }
        }
        left++;
        right--;
    }

    // Special case for odd number of elements
    if (left == right) {
        if (notify) {
            notify(SortEvent::Compare, left, right + 1, "Circle Midpoint Compare");
        }
        if (arr[left] > arr[right + 1]) {
            std::swap(arr[left], arr[right + 1]);
            swapped = true;
            if (notify) {
                notify(SortEvent::Swap, left, right + 1, "Circle Midpoint Swap");
            }
        }
    }

    int mid = low + (high - low) / 2;
    bool leftSwapped = circleSortRecursive(arr, low, mid, notify);
    bool rightSwapped = circleSortRecursive(arr, mid + 1, high, notify);

    return swapped || leftSwapped || rightSwapped;
}

void circleSort(std::vector<int>& arr, SortCallback notify) {
    if (arr.empty()) return;
    while (circleSortRecursive(arr, 0, static_cast<int>(arr.size()) - 1, notify)) {
        // Repeat until no swaps occur
    }
}