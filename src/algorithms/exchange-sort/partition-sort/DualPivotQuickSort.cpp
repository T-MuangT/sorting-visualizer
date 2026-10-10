#include <algorithm>
#include <string>
#include <cassert>

#include "../../../include/algorithms/PivotSelection.hpp"
#include "DualPivotQuickSort.hpp"

namespace dual_pivot_quicksort_internal {
    void dualPivotQuickSortRecursive(std::vector<int>& arr, int low, int high, SortCallback notify, DualPivotSelector selectPivots) {
        if (low >= high) {
            return;
        }

        PivotPair pivots = selectPivots(arr, low, high);

        // Normalize/validate pivot indices returned by selector
        int i1 = pivots.firstPivot;
        int i2 = pivots.secondPivot;
        if (i1 < low || i1 > high || i2 < low || i2 > high || i1 == i2) {
            assert(false && "DualPivotSelector returned invalid or duplicate pivot indices");
            i1 = low;
            i2 = high;
        }

        // Move chosen pivots into the `low` and `high` positions so the
        // partition algorithm can operate with pivots at the ends.
        if (i1 != low) {
            std::swap(arr[i1], arr[low]);
            if (notify) {
                notify(SortEvent::Swap, i1, low, "Yaroslavskiy Quicksort: Move Pivot 1 " + std::to_string(arr[i1]) + " to Low");
            }
            // If second pivot was at `low`, its index moved to i1.
            if (i2 == low) i2 = i1;
            i1 = low;
        }

        if (i2 != high) {
            std::swap(arr[i2], arr[high]);
            if (notify) {
                notify(SortEvent::Swap, i2, high, "Yaroslavskiy Quicksort: Move Pivot 2 " + std::to_string(arr[i2]) + " to High");
            }
            i2 = high;
        }

        // Ensure pivots are ordered: pivot1 <= pivot2
        if (arr[low] > arr[high]) {
            std::swap(arr[low], arr[high]);
            if (notify) {
                notify(SortEvent::Swap, low, high, "Yaroslavskiy Quicksort: Order Initial Pivots " + std::to_string(arr[i1]) + " and " + std::to_string(arr[i2])  + " at Ends");
            }
        }

        int p1 = arr[low];
        int p2 = arr[high];

        if (notify) {
            notify(SortEvent::Compare, low, high, "Yaroslavskiy Quicksort: Pivot Comparison between " + std::to_string(p1) + " and " + std::to_string(p2));
        }

        int less = low + 1;
        int great = high - 1;

        for (int k = less; k <= great; ++k) {
            if (notify) {
                notify(SortEvent::Compare, k, pivots.firstPivot, "Yaroslavskiy Quicksort: Compare " + std::to_string(arr[k]) + " with P1 " + std::to_string(p1));
            }

            if (arr[k] < p1) {
                if (k != less) {
                    std::swap(arr[k], arr[less]);

                    if (notify) {
                        notify(SortEvent::Swap, k, less, "Yaroslavskiy Quicksort: Swap " + std::to_string(arr[k]) + " < P1 " + std::to_string(p1));
                    }
                }

                ++less;
            } else {
                if (notify) {
                    notify(SortEvent::Compare, k, pivots.secondPivot, "Yaroslavskiy Quicksort: Compare " + std::to_string(arr[k]) + " with P2 " + std::to_string(p2));
                }

                if (arr[k] > p2) {
                    while (k < great && arr[great] > p2) {
                        if (notify) {
                            notify(SortEvent::Compare, great, pivots.secondPivot, "Yaroslavskiy Quicksort: Scan Right " + std::to_string(arr[k]) + " > P2 " + std::to_string(p2));
                        }

                        --great;
                    }

                    std::swap(arr[k], arr[great]);

                    if (notify) {
                        notify(SortEvent::Swap, k, great, "Yaroslavskiy Quicksort: Swap " + std::to_string(arr[k]) + " > P2 " + std::to_string(p2));
                    }

                    --great;

                    if (notify) {
                        notify(SortEvent::Compare, k, pivots.firstPivot, "Yaroslavskiy Quicksort: Re-check swapped elements with P1 " + std::to_string(p1));
                    }

                    if (arr[k] < p1) {
                        std::swap(arr[k], arr[less]);

                        if (notify) {
                            notify(SortEvent::Swap, k, less, "Yaroslavskiy Quicksort: Swap " + std::to_string(arr[k]) + " < P1 " + std::to_string(p1));
                        }

                        ++less;
                    }
                }
            }
        }

        --less;
        ++great;

        std::swap(arr[low], arr[less]);

        if (notify) {
            notify(SortEvent::Swap, low, less, "Yaroslavskiy Quicksort: Finalize P1 " + std::to_string(p1) + " Position");
        }

        std::swap(arr[high], arr[great]);

        if (notify) {
            notify(SortEvent::Swap, high, great, "Yaroslavskiy Quicksort: Finalize P2 " + std::to_string(p2) + " Position");
        }

        dualPivotQuickSortRecursive(arr, low, less - 1, notify, selectPivots);
        dualPivotQuickSortRecursive(arr, less + 1, great - 1, notify, selectPivots);
        dualPivotQuickSortRecursive(arr, great + 1, high, notify, selectPivots);
    }
}

void dualPivotQuickSort(std::vector<int>& arr, SortCallback notify, DualPivotSelector selectPivots) {
    if (!arr.empty()) {
        dual_pivot_quicksort_internal::dualPivotQuickSortRecursive(arr, 0, static_cast<int>(arr.size()) - 1, notify, selectPivots);
    }
}