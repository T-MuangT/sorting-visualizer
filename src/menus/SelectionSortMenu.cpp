#include "../include/menus/SelectionSortMenu.hpp"
#include <iostream>

// Include Selection Sort Branch Headers
#include "../algorithms/selection-sort/selection-sort/SelectionSort.hpp"
#include "../algorithms/selection-sort/selection-sort/DoubleSelectionSort.hpp"
#include "../algorithms/selection-sort/selection-sort/CycleSort.hpp"

// Include Heap Sort Branch Headers
#include "../algorithms/selection-sort/heap-sort/MaxHeapSort.hpp"
#include "../algorithms/selection-sort/heap-sort/MinHeapSort.hpp"
#include "../algorithms/selection-sort/heap-sort/SmoothSort.hpp"

AlgorithmRunner selectSelectionBranchAlgorithm() {
    std::cout << "\n--- Selection Sort Branch ---\n";
    std::cout << "  1. Selection Sort\n";
    std::cout << "  2. Double Selection Sort\n";
    std::cout << "  3. Cycle Sort\n";
    std::cout << "  0. Back\n";
    std::cout << "Choice: ";

    int choice = 0;
    std::cin >> choice;

    switch (choice) {
        case 1: return AlgorithmRunner::fromClassic(selectionSort);
        case 2: return AlgorithmRunner::fromClassic(doubleSelectionSort);
        case 3: return AlgorithmRunner::fromClassic(cycleSort);
        default: return AlgorithmRunner();
    }
}

AlgorithmRunner selectHeapBranchAlgorithm() {
    std::cout << "\n--- Heap Sort Branch ---\n";
    std::cout << "  1. Max Heapsort\n";
    std::cout << "  2. Min Heapsort\n";
    std::cout << "  3. Smoothsort\n";
    std::cout << "  0. Back\n";
    std::cout << "Choice: ";

    int choice = 0;
    std::cin >> choice;

    switch (choice) {
        case 1: return AlgorithmRunner::fromClassic(maxHeapSort);
        case 2: return AlgorithmRunner::fromClassic(minHeapSort);
        case 3: return AlgorithmRunner::fromClassic(smoothSort);
        default: return AlgorithmRunner();
    }
}

AlgorithmRunner selectSelectionFamilyAlgorithm() {
    std::cout << "\n--- Selection Sort Family ---\n";
    std::cout << "  1. Selection Sort Branch\n";
    std::cout << "  2. Heapsort Branch\n";
    std::cout << "  0. Back\n";
    std::cout << "Choice: ";

    int choice = 0;
    std::cin >> choice;

    switch (choice) {
        case 1: return selectSelectionBranchAlgorithm();
        case 2: return selectHeapBranchAlgorithm();
        default: return AlgorithmRunner();
    }
}