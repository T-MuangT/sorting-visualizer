#include <iostream>

#include "../include/menus/DistributionSortMenu.hpp"

// Include Pigeonhole Sort Branch Headers
#include "../algorithms/distribution-sort/pigeonhole-sort/PigeonholeSort.hpp"
#include "../algorithms/distribution-sort/counting-sort/CountingSort.hpp"

AlgorithmRunner selectPigeonholeBranchAlgorithm() {
    std::cout << "\n--- Pigeonhole Sort Branch ---\n";
    std::cout << "  1. Pigeonhole Sort\n";
    std::cout << "  0. Back\n";
    std::cout << "Choice: ";

    int choice = 0;
    std::cin >> choice;

    switch (choice) {
        case 1: return AlgorithmRunner::fromSession(pigeonholeSort);
        default: return AlgorithmRunner();
    }
}

AlgorithmRunner selectCountingBranchAlgorithm() {
    std::cout << "\n--- Counting Sort Branch ---\n";
    std::cout << "  1. Counting Sort\n";
    std::cout << "  0. Back\n";
    std::cout << "Choice: ";

    int choice = 0;
    std::cin >> choice;

    switch (choice) {
        case 1: return AlgorithmRunner::fromSession(countingSort);
        default: return AlgorithmRunner();
    }
}

AlgorithmRunner selectDistributionFamilyAlgorithm() {
    std::cout << "\n--- Distribution Sort Family ---\n";
    std::cout << "  1. Pigeonhole Sort Branch\n";
    std::cout << "  2. Counting Sort Branch\n";
    std::cout << "  0. Back\n";
    std::cout << "Choice: ";

    int choice = 0;
    std::cin >> choice;

    switch (choice) {
        case 1: return selectPigeonholeBranchAlgorithm();
        case 2: return selectCountingBranchAlgorithm();
        default: return AlgorithmRunner();
    }
}