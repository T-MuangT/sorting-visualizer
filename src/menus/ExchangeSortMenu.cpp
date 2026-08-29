#include "../include/menus/ExchangeSortMenu.hpp"
#include <iostream>

// Include Bubble Sort Family Headers
#include "../algorithms/exchange-sort/bubble-sort/BubbleSort.hpp"
#include "../algorithms/exchange-sort/bubble-sort/CocktailShakerSort.hpp"
#include "../algorithms/exchange-sort/bubble-sort/OptimizedCocktailShakerSort.hpp"
#include "../algorithms/exchange-sort/bubble-sort/OddEvenSort.hpp"
#include "../algorithms/exchange-sort/bubble-sort/CombSort.hpp"
#include "../algorithms/exchange-sort/bubble-sort/OptimizedCombSort.hpp"

// Include Partition Sort Family Headers
#include "../algorithms/exchange-sort/partition-sort/CircleSort.hpp"
#include "../algorithms/exchange-sort/partition-sort/LomutoQuickSort.hpp"
#include "../algorithms/exchange-sort/partition-sort/HoareQuickSort.hpp"
#include "../algorithms/exchange-sort/partition-sort/DualPivotQuickSort.hpp"
#include "../algorithms/exchange-sort/partition-sort/StableQuickSort.hpp"

AlgorithmRunner selectBubbleAlgorithm() {
    std::cout << "\n--- Bubble Sort Branch ---\n";
    std::cout << "  1. Standard Bubble Sort\n";
    std::cout << "  2. Cocktail Shaker Sort\n";
    std::cout << "  3. Optimized Cocktail Shaker Sort\n";
    std::cout << "  4. Odd-Even Sort\n";
    std::cout << "  5. Comb Sort\n";
    std::cout << "  6. Optimized Comb Sort\n";
    std::cout << "  0. Back\n";
    std::cout << "Choice: ";

    int choice = 0;
    std::cin >> choice;

    switch (choice) {
        case 1: return bubbleSort;
        case 2: return cocktailShakerSort;
        case 3: return optimizedCocktailShakerSort;
        case 4: return oddEvenSort;
        case 5: return combSort;
        case 6: return optimizedCombSort;
        default: return nullptr;
    }
}

AlgorithmRunner selectPartitionAlgorithm() {
    std::cout << "\n--- Partition Sort Branch ---\n";
    std::cout << "  1. Circle Sort\n";
    std::cout << "  2. Lomuto Partition (Left-Left)\n";
    std::cout << "  3. Hoare Partition (Left-Right)\n";
    std::cout << "  4. Dual-Pivot Quick Sort (Yaroslavskiy)\n";
    std::cout << "  5. Stable Quick Sort (Out-of-Place)\n";
    std::cout << "  0. Back\n";
    std::cout << "Choice: ";

    int choice = 0;
    std::cin >> choice;

    switch (choice) {
        case 1: return circleSort;
        case 2: return lomutoQuickSort;
        case 3: return hoareQuickSort;
        case 4: return dualPivotQuickSort;
        case 5: return stableQuickSort;
        default: return nullptr;
    }
}

AlgorithmRunner selectExchangeAlgorithm() {
    std::cout << "\n--- Exchange Sort Family ---\n";
    std::cout << "  1. Bubble Sort Branch\n";
    std::cout << "  2. Partition Sort Branch\n";
    std::cout << "  0. Back\n";
    std::cout << "Choice: ";

    int choice = 0;
    std::cin >> choice;

    switch (choice) {
        case 1: return selectBubbleAlgorithm();     // Invokes sub-menu
        case 2: return selectPartitionAlgorithm();  // Invokes sub-menu
        default: return nullptr;
    }
}