#include <iostream>

#include "../include/menus/ExchangeSortMenu.hpp"

// Include Bubble Sort Branch Headers
#include "../algorithms/exchange-sort/bubble-sort/BubbleSort.hpp"
#include "../algorithms/exchange-sort/bubble-sort/OptimizedBubbleSort.hpp"
#include "../algorithms/exchange-sort/bubble-sort/CocktailShakerSort.hpp"
#include "../algorithms/exchange-sort/bubble-sort/OptimizedCocktailShakerSort.hpp"
#include "../algorithms/exchange-sort/bubble-sort/OddEvenSort.hpp"
#include "../algorithms/exchange-sort/bubble-sort/OptimizedOddEvenSort.hpp"
#include "../algorithms/exchange-sort/bubble-sort/CombSort.hpp"
#include "../algorithms/exchange-sort/bubble-sort/OptimizedCombSort.hpp"

// Include Partition Sort Branch Headers
#include "../algorithms/exchange-sort/partition-sort/CircleSort.hpp"
#include "../algorithms/exchange-sort/partition-sort/OptimizedCircleSort.hpp"
#include "../algorithms/exchange-sort/partition-sort/StableQuickSort.hpp"

// Include Quicksort Pivot Selection Header
#include "../include/menus/exchange-sort/PivotSelectionMenu.hpp"

AlgorithmRunner selectBubbleBranchAlgorithm() {
    std::cout << "\n--- Bubble Sort Branch ---\n";
    std::cout << "  1. Bubble Sort\n";
    std::cout << "  2. Bubble Sort with Early Cutoff\n";
    std::cout << "  3. Cocktail Shaker Sort\n";
    std::cout << "  4. Cocktail Shaker Sort with Early Cutoff\n";
    std::cout << "  5. Odd-Even Sort\n";
    std::cout << "  6. Odd-Even Sort with Parallelism\n";
    std::cout << "  7. Comb Sort\n";
    std::cout << "  8. Comb Sort with Parallelism\n";
    std::cout << "  0. Back\n";
    std::cout << "Choice: ";

    int choice = 0;
    std::cin >> choice;

    switch (choice) {
        case 1: return AlgorithmRunner::fromClassic(bubbleSort);
        case 2: return AlgorithmRunner::fromClassic(optimizedBubbleSort);
        case 3: return AlgorithmRunner::fromClassic(cocktailShakerSort);
        case 4: return AlgorithmRunner::fromClassic(optimizedCocktailShakerSort);
        case 5: return AlgorithmRunner::fromClassic(oddEvenSort);
        case 6: return AlgorithmRunner::fromClassic(optimizedOddEvenSort);
        case 7: return AlgorithmRunner::fromClassic(combSort);
        case 8: return AlgorithmRunner::fromClassic(optimizedCombSort);
        default: return AlgorithmRunner();
    }
}

AlgorithmRunner selectPartitionBranchAlgorithm() {
    std::cout << "\n--- Partition Sort Branch ---\n";
    std::cout << "  1. Circle Sort\n";
    std::cout << "  2. Circle Sort with Parallelism\n";
    std::cout << "  3. Lomuto Partition (Left-Left Quicksort)\n";
    std::cout << "  4. Hoare Partition (Left-Right Quicksort)\n";
    std::cout << "  5. Yaroslavskiy Partition (Dual-Pivot Quicksort)\n";
    std::cout << "  6. Stable Quicksort (Out-of-Place)\n";
    std::cout << "  0. Back\n";
    std::cout << "Choice: ";

    int choice = 0;
    std::cin >> choice;

    switch (choice) {
        case 1: return AlgorithmRunner::fromClassic(circleSort);
        case 2: return AlgorithmRunner::fromClassic(optimizedCircleSort);
        case 3: return selectLomutoQuickSortPivotSelectionAlgorithm();
        case 4: return selectHoareQuickSortPivotSelectionAlgorithm();
        case 5: return selectDualPivotQuickSortPivotSelectionAlgorithm();
        case 6: return AlgorithmRunner::fromClassic(stableQuickSort);
        default: return AlgorithmRunner();
    }
}

AlgorithmRunner selectExchangeFamilyAlgorithm() {
    std::cout << "\n--- Exchange Sort Family ---\n";
    std::cout << "  1. Bubble Sort Branch\n";
    std::cout << "  2. Partition Sort Branch\n";
    std::cout << "  0. Back\n";
    std::cout << "Choice: ";

    int choice = 0;
    std::cin >> choice;

    switch (choice) {
        case 1: return selectBubbleBranchAlgorithm();
        case 2: return selectPartitionBranchAlgorithm();
        default: return AlgorithmRunner();
    }
}