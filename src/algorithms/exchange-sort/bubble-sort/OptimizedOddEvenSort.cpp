#include "OptimizedOddEvenSort.hpp"
#include <algorithm>
#include <string>
#include <omp.h>

void optimizedOddEvenSort(std::vector<int>& arr, SortCallback notify) {
    int n = static_cast<int>(arr.size());
    bool sorted = false;
    int phaseCount = 0;

    while (!sorted) {
        sorted = true;
        bool globalSwappedOdd = false;
        bool globalSwappedEven = false;

        // --- Optimized Odd Phase ---
        #pragma omp parallel
        {
            bool localSwapped = false;
            #pragma omp for schedule(static)
            for (int i = 1; i <= n - 2; i += 2) {
                if (arr[i] > arr[i + 1]) {
                    std::swap(arr[i], arr[i + 1]);
                    localSwapped = true;
                }
            }
            if (localSwapped) {
                #pragma omp write
                globalSwappedOdd = true;
            }
        }

        if (globalSwappedOdd) {
            sorted = false;
            if (notify) notify(SortEvent::Swap, -1, -1, "Optimized Odd-Even: Odd Phase Swap");
        }

        // --- Optimized Even Phase ---
        #pragma omp parallel
        {
            bool localSwapped = false;
            #pragma omp for schedule(static)
            for (int i = 0; i <= n - 2; i += 2) {
                if (arr[i] > arr[i + 1]) {
                    std::swap(arr[i], arr[i + 1]);
                    localSwapped = true;
                }
            }
            if (localSwapped) {
                #pragma omp write
                globalSwappedEven = true;
            }
        }

        if (globalSwappedEven) {
            sorted = false;
            if (notify) notify(SortEvent::Swap, -1, -1, "Optimized Odd-Even: Even Phase Swap");
        }
        
        ++phaseCount;
    }
}