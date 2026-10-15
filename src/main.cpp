#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <chrono>
#include <thread>

// Include Core Headers
#include "include/ArrayGenerator.hpp"
#include "include/AlgorithmRunner.hpp"

// Include Visualizer APIs
#include "include/visualizer/IArrayVisualizer.hpp"
#include "include/visualizer/ITableVisualizer.hpp"
#include "include/visualizer/IGraphVisualizer.hpp"
#include "include/visualizer/VisualizationSession.hpp"

// Include Terminal Main Menu
#include "include/menus/main-menu/TerminalMainMenu.hpp"

// Include Terminal Visualizer Implementations
#include "include/visualizer/terminal/TerminalArrayVisualizer.hpp"
#include "include/visualizer/terminal/TerminalTableVisualizer.hpp"
#include "include/visualizer/terminal/TerminalGraphVisualizer.hpp"
// #include "include/visualizer/GraphicsVisualizer.hpp" // For future GUI backend

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
        AlgorithmRunner selectedAlgorithm = selectMainMenuAlgorithm();

        if (!std::cin) {
            std::cout << "Exiting application...\n";
            break;
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
        std::unique_ptr<IGraphVisualizer> graphVisualizer;
        if (backend == RenderBackend::Terminal) {
            arrayVisualizer = std::make_unique<TerminalArrayVisualizer>(delayMs);
            tableVisualizer = std::make_unique<TerminalTableVisualizer>(delayMs);
            graphVisualizer = std::make_unique<TerminalGraphVisualizer>(delayMs);
        } else {
            // visualizer = std::make_unique<GraphicsVisualizer>(delayMs);
            std::cout << "[Graphics Backend coming soon, falling back to Terminal Visualizers]\n";
            arrayVisualizer = std::make_unique<TerminalArrayVisualizer>(delayMs);
            tableVisualizer = std::make_unique<TerminalTableVisualizer>(delayMs);
            graphVisualizer = std::make_unique<TerminalGraphVisualizer>(delayMs);
        }

        VisualizationSession session(*arrayVisualizer, *tableVisualizer, *graphVisualizer);

        std::cout << "\nStarting visualization in 3 seconds...\n";
        std::this_thread::sleep_for(std::chrono::seconds(3));

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
