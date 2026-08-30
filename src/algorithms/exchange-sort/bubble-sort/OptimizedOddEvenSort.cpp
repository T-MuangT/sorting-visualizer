#include "OptimizedOddEvenSort.hpp"
#include <algorithm>
#include <string>
#include <omp.h>

void optimizedOddEvenSort(std::vector<int>& arr, SortCallback notify) {
    int n = static_cast<int>(arr.size());
    if (n < 2) {
        return;
    }

    while (true) {
        bool swappedThisPass = false;

        for (int phase = 0; phase < 2; ++phase) {
            bool phaseSwapped = false;
            std::vector<int> swappedIndices;

            #pragma omp parallel
            {
                std::vector<int> localSwaps;

                #pragma omp for reduction(||: phaseSwapped) schedule(static)
                for (int i = phase; i <= n - 2; i += 2) {
                    int idx1 = i;
                    int idx2 = i + 1;

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
                swappedThisPass = true;
            }

            if (notify && !swappedIndices.empty()) {
                int highlight1 = swappedIndices.front();
                int highlight2 = swappedIndices.back();
                std::string phaseLabel = (phase == 0) ? "Odd Phase" : "Even Phase";
                notify(
                    SortEvent::Swap,
                    highlight1,
                    highlight2,
                    "Optimized Odd-Even: " + phaseLabel + " (" + std::to_string(swappedIndices.size() / 2) + " swaps)"
                );
            }
        }

        if (!swappedThisPass) {
            break;
        }
    }
}