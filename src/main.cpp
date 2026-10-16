#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <chrono>
#include <thread>
#include <limits>

// Include Core Headers
#include "include/ArrayGenerator.hpp"
#include "include/AlgorithmRunner.hpp"
#include "include/PresortConfig.hpp"

// Include Visualizer APIs
#include "include/visualizer/IArrayVisualizer.hpp"
#include "include/visualizer/ITableVisualizer.hpp"
#include "include/visualizer/IGraphVisualizer.hpp"
#include "include/visualizer/VisualizationSession.hpp"

// Include Terminal Menus
#include "include/menus/main-menu/TerminalMainMenu.hpp"
#include "include/menus/presort-menu/TerminalPresortMenu.hpp"

// Include Terminal Visualizer Implementations
#include "include/visualizer/terminal/TerminalArrayVisualizer.hpp"
#include "include/visualizer/terminal/TerminalTableVisualizer.hpp"
#include "include/visualizer/terminal/TerminalGraphVisualizer.hpp"
// #include "include/visualizer/GraphicsVisualizer.hpp" // For future GUI backend

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

        // Consume the newline left by selectBackend's std::cin >>.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Gather presort configuration
        PresortConfig config = selectPresortConfig();

        // Generate data based on user pattern choice
        auto data = ArrayGenerator::generate(config.arraySize, 1, 64, config.pattern);

        // Polymorphic backend instantiation
        std::unique_ptr<IArrayVisualizer> arrayVisualizer;
        std::unique_ptr<ITableVisualizer> tableVisualizer;
        std::unique_ptr<IGraphVisualizer> graphVisualizer;
        if (backend == RenderBackend::Terminal) {
            arrayVisualizer = std::make_unique<TerminalArrayVisualizer>(config.delayMs);
            tableVisualizer = std::make_unique<TerminalTableVisualizer>(config.delayMs);
            graphVisualizer = std::make_unique<TerminalGraphVisualizer>(config.delayMs);
        } else {
            // visualizer = std::make_unique<GraphicsVisualizer>(delayMs);
            std::cout << "[Graphics Backend coming soon, falling back to Terminal Visualizers]\n";
            arrayVisualizer = std::make_unique<TerminalArrayVisualizer>(config.delayMs);
            tableVisualizer = std::make_unique<TerminalTableVisualizer>(config.delayMs);
            graphVisualizer = std::make_unique<TerminalGraphVisualizer>(config.delayMs);
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
