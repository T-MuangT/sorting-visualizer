#include "OptimizedCircleSort.hpp"
#include <algorithm>
#include <string>
#include <omp.h>

namespace {
int optimizedCircleSortRecursive(std::vector<int>& arr, int low, int high, SortCallback notify) {
    if (low >= high) return 0;

    int swapped = 0;
    std::vector<int> swappedIndices;
    int lowIdx = low;
    int highIdx = high;

    while (lowIdx < highIdx) {
        if (arr[lowIdx] > arr[highIdx]) {
            std::swap(arr[lowIdx], arr[highIdx]);
            swapped = 1;
            swappedIndices.push_back(lowIdx);
            swappedIndices.push_back(highIdx);
        }
        ++lowIdx;
        --highIdx;
    }

    if (notify && !swappedIndices.empty()) {
        int highlight1 = swappedIndices.front();
        int highlight2 = swappedIndices.back();
        notify(
            SortEvent::Swap,
            highlight1,
            highlight2,
            "Optimized Circle: Batch Swap (" + std::to_string(swappedIndices.size() / 2) + " swaps)"
        );
    }

    int mid = low + (high - low) / 2;
    int leftSwapped = 0;
    int rightSwapped = 0;

    #pragma omp task shared(arr, notify) if(high - low > 64)
    leftSwapped = optimizedCircleSortRecursive(arr, low, mid, notify);

    #pragma omp task shared(arr, notify) if(high - low > 64)
    rightSwapped = optimizedCircleSortRecursive(arr, mid + 1, high, notify);

    #pragma omp taskwait

    return swapped || leftSwapped || rightSwapped;
}
} // anonymous namespace

void optimizedCircleSort(std::vector<int>& arr, SortCallback notify) {
    if (arr.empty()) return;

    #pragma omp parallel
    {
        #pragma omp single
        {
            while (true) {
                int swapped = optimizedCircleSortRecursive(arr, 0, static_cast<int>(arr.size()) - 1, notify);
                if (!swapped) break;
            }
        }
    }
}