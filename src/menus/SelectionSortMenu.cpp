#include "../include/menus/SelectionSortMenu.hpp"
#include <iostream>

#include "../algorithms/selection-sort/selection-sort/SelectionSort.hpp"
#include "../algorithms/selection-sort/selection-sort/DoubleSelectionSort.hpp"
#include "../algorithms/selection-sort/heap-sort/MaxHeapSort.hpp"
#include "../algorithms/selection-sort/heap-sort/MinHeapSort.hpp"

AlgorithmRunner selectSelectionBranchAlgorithm() {
    std::cout << "\n--- Selection Sort Branch ---\n";
    std::cout << "  1. Selection Sort\n";
    std::cout << "  2. Double Selection Sort\n";
    std::cout << "  0. Back\n";
    std::cout << "Choice: ";

    int choice = 0;
    std::cin >> choice;

    switch (choice) {
        case 1: return selectionSort;
        case 2: return doubleSelectionSort;
        default: return nullptr;
    }
}

AlgorithmRunner selectHeapBranchAlgorithm() {
    std::cout << "\n--- Heap Sort Branch ---\n";
    std::cout << "  1. Max Heap Sort\n";
    std::cout << "  2. Min Heap Sort\n";
    std::cout << "  0. Back\n";
    std::cout << "Choice: ";

    int choice = 0;
    std::cin >> choice;

    switch (choice) {
        case 1: return maxHeapSort;
        case 2: return minHeapSort;
        default: return nullptr;
    }
}

AlgorithmRunner selectSelectionFamilyAlgorithm() {
    std::cout << "\n--- Selection Sort Family ---\n";
    std::cout << "  1. Selection Sort Branch\n";
    std::cout << "  2. Heap Sort Branch\n";
    std::cout << "  0. Back\n";
    std::cout << "Choice: ";

    int choice = 0;
    std::cin >> choice;

    switch (choice) {
        case 1: return selectSelectionBranchAlgorithm();
        case 2: return selectHeapBranchAlgorithm();
        default: return nullptr;
    }
}