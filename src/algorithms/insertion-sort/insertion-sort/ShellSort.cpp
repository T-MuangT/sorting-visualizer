#include "ShellSort.hpp"
#include <algorithm>
#include <string>

void shellSort(std::vector<int>& arr, SortCallback notify) {
    int n = static_cast<int>(arr.size());
    int gap = n / 2;
    const double shrink = 1.3;

    while (gap > 0) {
        for (int i = gap; i < n; ++i) {
            int key = arr[i];
            int j = i;

            while (j >= gap) {
                if (notify) {
                    notify(SortEvent::Compare, j - gap, i, "Shellsort: Gap Compare " + std::to_string(gap));
                }

                if (arr[j - gap] <= key) {
                    break;
                }
            
                arr[j] = arr[j - gap];

                if (notify){
                notify(SortEvent::Shift, j - gap, j, "Shellsort: Gap Shift");
                }
                j -= gap;
            }
            arr[j] = key;

            if (notify) {
                notify(SortEvent::Insert, i, j, "Shellsort: Gap Insert");
            }
        }
        gap = static_cast<int>(gap / shrink);
    }
}