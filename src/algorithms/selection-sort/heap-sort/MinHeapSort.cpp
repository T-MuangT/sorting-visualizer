#include "MinHeapSort.hpp"
#include <algorithm>

namespace {
void minHeapify(std::vector<int>& arr, int n, int i, SortCallback notify) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n) {
        if (notify) notify(SortEvent::Compare, left, smallest, "Min-Heapify: Compare Left Child");
        if (arr[left] < arr[smallest]) {
            smallest = left;
        }
    }

    if (right < n) {
        if (notify) notify(SortEvent::Compare, right, smallest, "Min-Heapify: Compare Right Child");
        if (arr[right] < arr[smallest]) {
            smallest = right;
        }
    }

    if (smallest != i) {
        std::swap(arr[i], arr[smallest]);
        if (notify) notify(SortEvent::Swap, i, smallest, "Min-Heapify: Swap to Maintain Min-Heap");
        minHeapify(arr, n, smallest, notify);
    }
}
} // anonymous namespace

void minHeapSort(std::vector<int>& arr, SortCallback notify) {
    int n = static_cast<int>(arr.size());

    // Build min heap
    for (int i = n / 2 - 1; i >= 0; --i) {
        minHeapify(arr, n, i, notify);
    }

    // Extract elements from min-heap one by one (results in descending order, 
    // so we reverse at the end or place them correctly to yield sorted order)
    for (int i = n - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        if (notify) notify(SortEvent::Swap, 0, i, "Min Heap: Extract Root to End");
        minHeapify(arr, i, 0, notify);
    }
    
    // Min-heap extraction naturally sorts descending; reverse to match ascending visualizer contract
    std::reverse(arr.begin(), arr.end());
}