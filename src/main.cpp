#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <chrono>
#include <thread>

// Include Core Headers
#include "include/ArrayGenerator.hpp"
#include "include/AlgorithmRunner.hpp"

// Include Menus
#include "include/menus/ExchangeSortMenu.hpp"
#include "include/menus/SelectionSortMenu.hpp"
#include "include/menus/InsertionSortMenu.hpp"
#include "include/menus/MergeSortMenu.hpp"
#include "include/menus/DistributionSortMenu.hpp"

// Include Visualizers
#include "include/visualizer/IArrayVisualizer.hpp"
#include "include/visualizer/ITableVisualizer.hpp"
#include "include/visualizer/TerminalArrayVisualizer.hpp"
#include "include/visualizer/TerminalTableVisualizer.hpp"
#include "include/visualizer/VisualizationSession.hpp"
// #include "include/visualizer/GraphicsVisualizer.hpp" // For future GUI backend

void displayMainMenu() {
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

Pattern selectPattern() {
    std::cout << "\nSelect Array Data Pattern:\n";
    std::cout << "  1. Uniform Random\n";
    std::cout << "  2. Reverse Sorted\n";
    std::cout << "  3. Nearly Sorted\n";
    std::cout << "Choice [1-3]: ";

    int choice = 1;
    std::cin >> choice;

    switch (choice) {
        case 2:  return Pattern::ReverseSorted;
        case 3:  return Pattern::NearlySorted;
        default: return Pattern::UniformRandom;
    }
}

AlgorithmRunner selectPlaceholderMenu(const std::string& familyName) {
    std::cout << "\n--- " << familyName << " ---\n";
    std::cout << "  [Under Construction - Variants coming soon]\n";
    std::cout << "  0. Back\n";
    std::cout << "Choice: ";
    int choice;
    std::cin >> choice;
    return {};
}

enum class RenderBackend {
    Terminal,
    Graphics
};

RenderBackend selectBackend() {
    std::cout << "\nSelect Rendering Mode:\n";
    std::cout << "  1. Terminal Mode\n";
    std::cout << "  2. Graphics Mode\n";
    std::cout << "Choice [1-2]: ";

    int choice = 1;
    std::cin >> choice;
    return (choice == 2) ? RenderBackend::Graphics : RenderBackend::Terminal;
}

int main() {
    while (true) {
        displayMainMenu();
        int familyChoice = 0;
        if (!(std::cin >> familyChoice) || familyChoice == 0) {
            std::cout << "Exiting application...\n";
            break;
        }

        AlgorithmRunner selectedAlgorithm{};

        switch (familyChoice) {
            case 1:
                selectedAlgorithm = selectExchangeFamilyAlgorithm();
                break;
            case 2:
                selectedAlgorithm = selectSelectionFamilyAlgorithm();
                break;
            case 3:
                selectedAlgorithm = selectInsertionFamilyAlgorithm();
                break;
            case 4:
                selectedAlgorithm = selectMergeFamilyAlgorithm();
                break;
            case 5:
                selectedAlgorithm = selectDistributionFamilyAlgorithm();
                break;
            case 6:
                selectedAlgorithm = selectPlaceholderMenu("Concurrent Sort Family");
                break;
            case 7:
                selectedAlgorithm = selectPlaceholderMenu("Miscellaneous Sort Family");
                break;
            case 8:
                selectedAlgorithm = selectPlaceholderMenu("Hybrid Sort Family");
                break;
            case 9:
                selectedAlgorithm = selectPlaceholderMenu("Impractical Sort Family");
                break;
            default:
                std::cout << "Invalid family choice.\n\n";
                continue;
        }

        if (!selectedAlgorithm) {
            continue;
        }

        // Prompt for backend strategy
        RenderBackend backend = selectBackend();
        Pattern pattern = selectPattern();

        size_t arraySize = 32;
        std::cout << "Enter Array Size [default 32]: ";
        std::cin >> arraySize;

        int delayMs = 100;
        std::cout << "Enter Frame Delay (ms) [default 100]: ";
        std::cin >> delayMs;

        // Generate data based on user pattern choice
        auto data = ArrayGenerator::generate(arraySize, 1, 64, pattern);

        // Polymorphic backend instantiation
        std::unique_ptr<IArrayVisualizer> arrayVisualizer;
        std::unique_ptr<ITableVisualizer> tableVisualizer;
        if (backend == RenderBackend::Terminal) {
            arrayVisualizer = std::make_unique<TerminalArrayVisualizer>(delayMs);
            tableVisualizer = std::make_unique<TerminalTableVisualizer>(delayMs);
        } else {
            // visualizer = std::make_unique<GraphicsVisualizer>(delayMs);
            std::cout << "[Graphics Backend coming soon, falling back to Terminal Visualizers]\n";
            arrayVisualizer = std::make_unique<TerminalArrayVisualizer>(delayMs);
            tableVisualizer = std::make_unique<TerminalTableVisualizer>(delayMs);
        }

        VisualizationSession session(*arrayVisualizer, *tableVisualizer);

        std::cout << "\nStarting visualization in 2 seconds...\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));

        // Execute selected algorithm through the session-aware runner.
        selectedAlgorithm(data, session);

        // Final completion render frame
        session.onArrayEvent(data, SortEvent::Compare, -1, -1, "Sorting Complete!");
        
        std::cout << "\nPress Enter to return to main menu...";
        std::cin.ignore();
        std::cin.get();
        std::cout << "\n";
    }

    return 0;
}
