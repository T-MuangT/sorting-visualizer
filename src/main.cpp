#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <chrono>
#include <thread>
#include <functional>

// Include Core Types & Generator
#include "include/Types.hpp"
#include "include/ArrayGenerator.hpp"

// Include Menus
#include "include/menus/ExchangeSortMenu.hpp"

// Include Visualizers
#include "include/SortStats.hpp"
#include "include/visualizer/IVisualizer.hpp"
#include "include/visualizer/TerminalVisualizer.hpp"
// #include "include/visualizer/GraphicsVisualizer.hpp" // For future GUI backend

// Include Exchange Algorithms
#include "algorithms/exchange-sort/bubble-sort/BubbleSort.hpp"
#include "algorithms/exchange-sort/bubble-sort/CocktailShakerSort.hpp"
#include "algorithms/exchange-sort/bubble-sort/OptimizedCocktailShakerSort.hpp"
#include "algorithms/exchange-sort/bubble-sort/OddEvenSort.hpp"
#include "algorithms/exchange-sort/bubble-sort/CombSort.hpp"
#include "algorithms/exchange-sort/bubble-sort/OptimizedCombSort.hpp"
#include "algorithms/exchange-sort/partition-sort/CircleSort.hpp"
#include "algorithms/exchange-sort/partition-sort/LomutoQuickSort.hpp"
#include "algorithms/exchange-sort/partition-sort/HoareQuickSort.hpp"
#include "algorithms/exchange-sort/partition-sort/DualPivotQuickSort.hpp"
#include "algorithms/exchange-sort/partition-sort/StableQuickSort.hpp"

using AlgorithmRunner = std::function<void(std::vector<int>&, SortCallback)>;

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
    return nullptr;
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

        AlgorithmRunner selectedAlgorithm = nullptr;

        switch (familyChoice) {
            case 1:
                selectedAlgorithm = selectExchangeAlgorithm();
                break;
            case 2:
                selectedAlgorithm = selectPlaceholderMenu("Selection Sort Family");
                break;
            case 3:
                selectedAlgorithm = selectPlaceholderMenu("Insertion Sort Family");
                break;
            case 4:
                selectedAlgorithm = selectPlaceholderMenu("Merge Sort Family");
                break;
            case 5:
                selectedAlgorithm = selectPlaceholderMenu("Distribution Sort Family");
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
        std::unique_ptr<IVisualizer> visualizer;
        if (backend == RenderBackend::Terminal) {
            visualizer = std::make_unique<TerminalVisualizer>(delayMs);
        } else {
            // visualizer = std::make_unique<GraphicsVisualizer>(delayMs);
            std::cout << "[Graphics Backend coming soon, falling back to Terminal Visualizer]\n";
            visualizer = std::make_unique<TerminalVisualizer>(delayMs);
        }

        // State tracker
        SortStats stats;

        // Callback captures visualizer pointer and calls renderFrame
        auto callback = [&data, &visualizer, &stats](SortEvent event, int i1, int i2, const std::string& step) {
            stats.recordEvent(event);
            visualizer->renderFrame(data, event, i1, i2, step, stats);
        };

        std::cout << "\nStarting visualization in 2 seconds...\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));

        // Execute selected algorithm via std::function runner
        selectedAlgorithm(data, callback);

        // Final completion render frame
        visualizer->renderFrame(data, SortEvent::Compare, -1, -1, "Sorting Complete!", stats);
        
        std::cout << "\nPress Enter to return to main menu...";
        std::cin.ignore();
        std::cin.get();
        std::cout << "\n";
    }

    return 0;
}