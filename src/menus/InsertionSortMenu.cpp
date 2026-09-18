#include "../include/menus/InsertionSortMenu.hpp"
#include <iostream>

// Include Insertion Sort Branch Headers
#include "../algorithms/insertion-sort/insertion-sort/InsertionSort.hpp"
//#include "../algorithms/insertion-sort/insertion-sort/BinaryInsertionSort.hpp"
//#include "../algorithms/insertion-sort/insertion-sort/ShellSort.hpp"

// Include Tree Sort Branch Headers
//#include "../algorithms/insertion-sort/tree-sort/TreeSort.hpp"

AlgorithmRunner selectInsertionBranchAlgorithm() {
    std::cout << "\n--- Insertion Sort Branch ---\n";
    std::cout << "  1. Insertion Sort\n";
    // std::cout << "  2. Binary Insertion Sort\n";
    // std::cout << "  3. Shell Sort\n";
    std::cout << "  0. Back\n";
    std::cout << "Choice: ";

    int choice = 0;
    std::cin >> choice;

    switch (choice) {
        case 1: return AlgorithmRunner::fromClassic(insertionSort);
        // case 2: return AlgorithmRunner(binaryInsertionSort);
        // case 3: return AlgorithmRunner(shellSort);
        default: return AlgorithmRunner();
    }
}

/*AlgorithmRunner selectTreeBranchAlgorithm() {
    std::cout << "\n--- Tree Sort Branch ---\n";
    std::cout << "  1. Tree Sort\n";
    std::cout << "  0. Back\n";
    std::cout << "Choice: ";

    int choice = 0;
    std::cin >> choice;

    switch (choice) {
        case 1: return treeSort;
        default: return nullptr;
    }
}*/

AlgorithmRunner selectInsertionFamilyAlgorithm() {
    std::cout << "\n--- Insertion Sort Family ---\n";
    std::cout << "  1. Insertion Sort Branch\n";
    // std::cout << "  2. Tree Sort Branch\n";
    std::cout << "  0. Back\n";
    std::cout << "Choice: ";

    int choice = 0;
    std::cin >> choice;

    switch (choice) {
        case 1: return selectInsertionBranchAlgorithm();
        // case 2: return selectTreeBranchAlgorithm();
        default: return AlgorithmRunner();
    }
}