#include "../include/menus/DistributionSortMenu.hpp"
#include <iostream>

// Include Pigeonhole Sort Branch Headers
#include "../algorithms/distribution-sort/pigeonhole-sort/PigeonholeSort.hpp"

AlgorithmRunner selectPigeonholeBranchAlgorithm() {
    std::cout << "\n--- Selection Sort Branch ---\n";
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

AlgorithmRunner selectDistributionFamilyAlgorithm() {
    std::cout << "\n--- Distribution Sort Family ---\n";
    std::cout << "  1. Pigeonhole Sort Branch\n";
    std::cout << "  0. Back\n";
    std::cout << "Choice: ";

    int choice = 0;
    std::cin >> choice;

    switch (choice) {
        case 1: return selectPigeonholeBranchAlgorithm();
        default: return AlgorithmRunner();
    }
}