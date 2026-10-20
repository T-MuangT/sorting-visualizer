#include <iostream>
#include <cstdlib>

#include "../../include/menus/terminal/TerminalMainMenu.hpp"

// Include algorithm-family menus
#include "../../include/menus/terminal/sort-menu/TerminalExchangeSortMenu.hpp"
#include "../../include/menus/terminal/sort-menu/TerminalSelectionSortMenu.hpp"
#include "../../include/menus/terminal/sort-menu/TerminalInsertionSortMenu.hpp"
#include "../../include/menus/terminal/sort-menu/TerminalMergeSortMenu.hpp"
#include "../../include/menus/terminal/sort-menu/TerminalDistributionSortMenu.hpp"

void displayMainMenu()
{
    std::cout << "===========================================\n";
    std::cout << "         ALGORITHM VISUALIZER ENGINE       \n";
    std::cout << "===========================================\n";
    std::cout << "Select Algorithm Family:\n";
    std::cout << "  1. Exchange Sorts\n";
    std::cout << "  2. Selection Sorts\n";
    std::cout << "  3. Insertion Sorts\n";
    std::cout << "  4. Merge Sorts\n";
    std::cout << "  5. Distribution Sorts\n";
    std::cout << "  6. Concurrent Sorts\n";
    std::cout << "  7. Miscellaneous Sorts\n";
    std::cout << "  8. Hybrid Sorts\n";
    std::cout << "  9. Impractical Sorts\n";
    std::cout << "  0. Exit\n";
    std::cout << "-------------------------------------------\n";
    std::cout << "Choice: ";
}

AlgorithmRunner selectPlaceholderMenu(const std::string& familyName)
{
    std::cout << "\n--- " << familyName << " ---\n";
    std::cout << "  [Under Construction - Variants coming soon]\n";
    std::cout << "  0. Back\n";
    std::cout << "Choice: ";

    int choice{};
    std::cin >> choice;

    return {};
}

AlgorithmRunner selectMainMenuAlgorithm(bool& shouldExit)
{
    displayMainMenu();

    int familyChoice = 0;

    if (!(std::cin >> familyChoice)) {
        return {};
    }

    switch (familyChoice) {
        case 1:
            return selectExchangeFamilyAlgorithm();

        case 2:
            return selectSelectionFamilyAlgorithm();

        case 3:
            return selectInsertionFamilyAlgorithm();

        case 4:
            return selectMergeFamilyAlgorithm();

        case 5:
            return selectDistributionFamilyAlgorithm();

        case 6:
            return selectPlaceholderMenu("Concurrent Sort Family");

        case 7:
            return selectPlaceholderMenu("Miscellaneous Sort Family");

        case 8:
            return selectPlaceholderMenu("Hybrid Sort Family");

        case 9:
            return selectPlaceholderMenu("Impractical Sort Family");

        case 0:
            shouldExit = true;
            return {};

        default:
            std::cout << "Invalid input.\nChoice: ";
            return {};
    }
}