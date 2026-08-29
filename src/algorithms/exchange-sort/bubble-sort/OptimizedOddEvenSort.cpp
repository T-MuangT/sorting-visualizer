#include "OptimizedOddEvenSort.hpp"
#include <algorithm>
#include <string>
#include <omp.h>

void optimizedOddEvenSort(std::vector<int>& arr, SortCallback notify) {
    int n = static_cast<int>(arr.size());
    if (n < 2) {
        return;
    }

    bool swappedThisPass = false;

    while (true) {
        swappedThisPass = false;

        // Odd phase: pairs (1,2), (3,4), ... are independent and can run in parallel.
        #pragma omp parallel for schedule(static) reduction(||: swappedThisPass)
        for (int i = 1; i <= n - 2; i += 2) {
            if (notify) {
                #pragma omp critical
                {
                    notify(SortEvent::Compare, i, i + 1, "Optimized Odd-Even: Odd Phase Compare");
                }
            }

            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                swappedThisPass = true;
                if (notify) {
                    #pragma omp critical
                    {
                        notify(SortEvent::Swap, i, i + 1, "Optimized Odd-Even: Odd Phase Swap");
                    }
                }
            }
        }

        // Even phase: pairs (0,1), (2,3), ... are independent and can run in parallel.
        #pragma omp parallel for schedule(static) reduction(||: swappedThisPass)
        for (int i = 0; i <= n - 2; i += 2) {
            if (notify) {
                #pragma omp critical
                {
                    notify(SortEvent::Compare, i, i + 1, "Optimized Odd-Even: Even Phase Compare");
                }
            }

            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                swappedThisPass = true;
                if (notify) {
                    #pragma omp critical
                    {
                        notify(SortEvent::Swap, i, i + 1, "Optimized Odd-Even: Even Phase Swap");
                    }
                }
            }
        }

        if (!swappedThisPass) {
            break;
        }
    }
}