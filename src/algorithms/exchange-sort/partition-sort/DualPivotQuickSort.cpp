#include "DualPivotQuickSort.hpp"
#include <algorithm>

namespace {
void dualPivotQuickSortRecursive(std::vector<int>& arr, int low, int high, SortCallback notify) {
    if (low >= high) return;

    if (notify) notify(SortEvent::Compare, low, high, "Dual-Pivot: Pivot Comparison");
    if (arr[low] > arr[high]) {
        std::swap(arr[low], arr[high]);
        if (notify) notify(SortEvent::Swap, low, high, "Dual-Pivot: Order Initial Pivots");
    }

    int p1 = arr[low];
    int p2 = arr[high];
    int less = low + 1;
    int great = high - 1;

    for (int k = less; k <= great; ++k) {
        if (notify) notify(SortEvent::Compare, k, low, "Dual-Pivot: Compare with P1");
        if (arr[k] < p1) {
            if (k != less) {
                std::swap(arr[k], arr[less]);
                if (notify) notify(SortEvent::Swap, k, less, "Dual-Pivot: Swap < P1");
            }
            ++less;
        } else {
            if (notify) notify(SortEvent::Compare, k, high, "Dual-Pivot: Compare with P2");
            if (arr[k] > p2) {
                while (k < great && arr[great] > p2) {
                    if (notify) notify(SortEvent::Compare, great, high, "Dual-Pivot: Scan Right > P2");
                    --great;
                }
                std::swap(arr[k], arr[great]);
                if (notify) notify(SortEvent::Swap, k, great, "Dual-Pivot: Swap > P2");
                --great;

                if (notify) notify(SortEvent::Compare, k, low, "Dual-Pivot: Re-check swapped with P1");
                if (arr[k] < p1) {
                    std::swap(arr[k], arr[less]);
                    if (notify) notify(SortEvent::Swap, k, less, "Dual-Pivot: Swap < P1");
                    ++less;
                }
            }
        }
    }

    --less;
    ++great;

    std::swap(arr[low], arr[less]);
    if (notify) notify(SortEvent::Swap, low, less, "Dual-Pivot: Finalize P1 Position");

    std::swap(arr[high], arr[great]);
    if (notify) notify(SortEvent::Swap, high, great, "Dual-Pivot: Finalize P2 Position");

    dualPivotQuickSortRecursive(arr, low, less - 1, notify);
    dualPivotQuickSortRecursive(arr, less + 1, great - 1, notify);
    dualPivotQuickSortRecursive(arr, great + 1, high, notify);
}
} // anonymous namespace

void dualPivotQuickSort(std::vector<int>& arr, SortCallback notify) {
    if (!arr.empty()) {
        dualPivotQuickSortRecursive(arr, 0, static_cast<int>(arr.size()) - 1, notify);
    }
}