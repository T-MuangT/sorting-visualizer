#include <iostream>

#include "../include/menus/MergeSortMenu.hpp"

// Include Merge Sort Headers
#include "../algorithms/merge-sort/MergeSort.hpp"

AlgorithmRunner selectMergeFamilyAlgorithm() {
    std::cout << "\n--- Merge Sort Family ---\n";
    std::cout << "  1. Merge Sort\n";
    std::cout << "  0. Back\n";
    std::cout << "Choice: ";

    int choice = 0;
    std::cin >> choice;

    switch (choice) {
        case 1: return AlgorithmRunner::fromSession(mergeSort);
        default: return AlgorithmRunner();
    }
}
