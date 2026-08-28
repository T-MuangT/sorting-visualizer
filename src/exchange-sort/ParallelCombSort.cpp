#include "ParallelCombSort.hpp"
#include <algorithm>
#include <string>
#include <omp.h>

void parallelCombSort(std::vector<int>& arr, SortCallback notify) {
    int n = static_cast<int>(arr.size());
    int gap = n;
    bool swapped = true;
    const double shrink = 1.3;

    while (gap > 1 || swapped) {
        gap = static_cast<int>(gap / shrink);
        if (gap == 9 || gap == 10) gap = 11; // Comb Sort 11 rule
        if (gap < 1) gap = 1;

        swapped = false;
        int maxSteps = (n - gap + 1) / 2;

        for (int step = 0; step < maxSteps; ++step) {
            bool stepSwapped = false;

            #pragma omp parallel for reduction(|:stepSwapped) schedule(static)
            for (int phase = 0; phase < 2; ++phase) {
                int i = phase + step * 2;
                if (i < n - gap) {
                    int idx1 = i;
                    int idx2 = i + gap;

                    if (arr[idx1] > arr[idx2]) {
                        std::swap(arr[idx1], arr[idx2]);
                        stepSwapped = true;
                    }
                }
            }

            if (stepSwapped) {
                swapped = true;
            }

            if (notify) {
                notify(SortEvent::Compare, step, gap, "Parallel Step " + std::to_string(step));
            }
        }
    }
}