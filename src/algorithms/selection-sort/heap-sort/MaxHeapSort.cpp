#include "MaxHeapSort.hpp"
#include <algorithm>

namespace {
void heapify(std::vector<int>& arr, int n, int i, SortCallback notify) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n) {
        if (notify) notify(SortEvent::Compare, left, largest, "Heapify: Compare Left Child");
        if (arr[left] > arr[largest]) {
            largest = left;
        }
    }

    if (right < n) {
        if (notify) notify(SortEvent::Compare, right, largest, "Heapify: Compare Right Child");
        if (arr[right] > arr[largest]) {
            largest = right;
        }
    }

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        if (notify) notify(SortEvent::Swap, i, largest, "Heapify: Swap to Maintain Max-Heap");
        heapify(arr, n, largest, notify);
    }
}
} // anonymous namespace

void maxHeapSort(std::vector<int>& arr, SortCallback notify) {
    int n = static_cast<int>(arr.size());

    // Build max heap
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(arr, n, i, notify);
    }

    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        if (notify) notify(SortEvent::Swap, 0, i, "Max Heap: Extract Root to End");
        heapify(arr, i, 0, notify);
    }
}