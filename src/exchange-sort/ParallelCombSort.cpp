#include "ParallelCombSort.hpp"
#include <algorithm>
#include <string>
#include <vector>
#include <omp.h>

void parallelCombSort(std::vector<int>& arr, SortCallback notify) {
    int n = static_cast<int>(arr.size());
    int gap = n;
    bool swapped = true;
    const double shrink = 1.3;
    int passNumber = 1;

    while (gap > 1 || swapped) {
        gap = static_cast<int>(gap / shrink);
        if (gap == 9 || gap == 10) gap = 11;
        if (gap < 1) gap = 1;

        swapped = false;
        
        // Track indices swapped during both phases of this gap pass
        std::vector<int> swappedIndices;

        // Run Phase 0 and Phase 1 silently in parallel
        for (int phase = 0; phase < 2; ++phase) {
            bool phaseSwapped = false;

            #pragma omp parallel
            {
                std::vector<int> localSwaps;

                #pragma omp for reduction(|:phaseSwapped) schedule(static)
                for (int i = phase; i < n - gap; i += 2) {
                    int idx1 = i;
                    int idx2 = i + gap;

                    if (arr[idx1] > arr[idx2]) {
                        std::swap(arr[idx1], arr[idx2]);
                        phaseSwapped = true;
                        localSwaps.push_back(idx1);
                        localSwaps.push_back(idx2);
                    }
                }

                #pragma omp critical
                {
                    swappedIndices.insert(swappedIndices.end(), localSwaps.begin(), localSwaps.end());
                }
            }

            if (phaseSwapped) {
                swapped = true;
            }
        }

        // Render ONCE per completed gap pass
        if (notify) {
            int highlight1 = swappedIndices.empty() ? -1 : swappedIndices.front();
            int highlight2 = swappedIndices.empty() ? -1 : swappedIndices.back();

            notify(
                swappedIndices.empty() ? SortEvent::Compare : SortEvent::Swap,
                highlight1,
                highlight2,
                "Gap " + std::to_string(gap) + " Pass #" + std::to_string(passNumber++) +
                " (" + std::to_string(swappedIndices.size() / 2) + " swaps)"
            );
        }
    }
}