#include <iostream>
#include <vector>

#include "../../include/menus/exchange-sort/PivotSelectionMenu.hpp"
#include "../../include/algorithms/PivotSelection.hpp"

#include "../../algorithms/exchange-sort/partition-sort/LomutoQuickSort.hpp"
#include "../../algorithms/exchange-sort/partition-sort/HoareQuickSort.hpp"
#include "../../algorithms/exchange-sort/partition-sort/DualPivotQuickSort.hpp"

AlgorithmRunner selectLomutoQuickSortPivotSelectionAlgorithm() {
    std::cout << "\n--- Lomuto Quicksort: Pivot Selection ---\n";
    std::cout << "  1. First Element\n";
    std::cout << "  2. Last Element\n";
    std::cout << "  3. Middle Element\n";
    std::cout << "  4. Random Element\n";
    std::cout << "  5. Median of Three\n";
    std::cout << "  0. Back\n";
    std::cout << "Choice: ";

    int choice = 0;
    std::cin >> choice;

    switch (choice) {
        case 1:
            return AlgorithmRunner::fromClassic([](std::vector<int>& arr, SortCallback notify) {
                    lomutoQuickSort(arr, notify, firstIndexPivot);
                }
            );

        case 2:
            return AlgorithmRunner::fromClassic([](std::vector<int>& arr, SortCallback notify) {
                    lomutoQuickSort(arr, notify, lastIndexPivot);
                }
            );

        case 3:
            return AlgorithmRunner::fromClassic([](std::vector<int>& arr, SortCallback notify) {
                    lomutoQuickSort(arr, notify, middleIndexPivot);
                }
            );

        case 4:
            return AlgorithmRunner::fromClassic([](std::vector<int>& arr, SortCallback notify) {
                    lomutoQuickSort(arr, notify, randomIndexPivot);
                }
            );

        case 5:
            return AlgorithmRunner::fromClassic([](std::vector<int>& arr, SortCallback notify) {
                    lomutoQuickSort(arr, notify, medianOfThreePivot);
                }
            );

        default:
            return {};
    }
}

AlgorithmRunner selectHoareQuickSortPivotSelectionAlgorithm() {
    std::cout << "\n--- Hoare Quicksort: Pivot Selection ---\n";
    std::cout << "  1. First Element\n";
    std::cout << "  2. Last Element\n";
    std::cout << "  3. Middle Element\n";
    std::cout << "  4. Random Element\n";
    std::cout << "  5. Median of Three\n";
    std::cout << "  0. Back\n";
    std::cout << "Choice: ";

    int choice = 0;
    std::cin >> choice;

    switch (choice) {
        case 1:
            return AlgorithmRunner::fromClassic([](std::vector<int>& arr, SortCallback notify) {
                    hoareQuickSort(arr, notify, firstIndexPivot);
                }
            );

        case 2:
            return AlgorithmRunner::fromClassic([](std::vector<int>& arr, SortCallback notify) {
                    hoareQuickSort(arr, notify, lastIndexPivot);
                }
            );

        case 3:
            return AlgorithmRunner::fromClassic([](std::vector<int>& arr, SortCallback notify) {
                    hoareQuickSort(arr, notify, middleIndexPivot);
                }
            );

        case 4:
            return AlgorithmRunner::fromClassic([](std::vector<int>& arr, SortCallback notify) {
                    hoareQuickSort(arr, notify, randomIndexPivot);
                }
            );

        case 5:
            return AlgorithmRunner::fromClassic([](std::vector<int>& arr, SortCallback notify) {
                    hoareQuickSort(arr, notify, medianOfThreePivot);
                }
            );

        default:
            return {};
    }
}

AlgorithmRunner selectDualPivotQuickSortPivotSelectionAlgorithm() {
    std::cout << "\n--- Yaroslavskiy Quicksort: Pivot Selection ---\n";
    std::cout << "  1. First and Last Elements\n";
    std::cout << "  2. Two Random Elements\n";
    std::cout << "  3. Two Median Elements from Two Quartiles (Q1/Q3)\n";
    std::cout << "  0. Back\n";
    std::cout << "Choice: ";

    int choice = 0;
    std::cin >> choice;

    switch (choice) {
        case 1:
            return AlgorithmRunner::fromClassic([](std::vector<int>& arr, SortCallback notify) {
                    dualPivotQuickSort(arr, notify, firstAndLastIndicesPivots);
                }
            );

        case 2:
            return AlgorithmRunner::fromClassic([](std::vector<int>& arr, SortCallback notify) {
                    dualPivotQuickSort(arr, notify, twoRandomIndicesPivots);
                }
            );

        case 3:
            return AlgorithmRunner::fromClassic([](std::vector<int>& arr, SortCallback notify) {
                    dualPivotQuickSort(arr, notify, twoQuartileMediansPivots);
                }
            );

        default:
            return {};
    }
}