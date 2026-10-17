#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <chrono>
#include <thread>
#include <limits>

// Include Core Headers
#include "../include/ArrayGenerator.hpp"
#include "../include/AlgorithmRunner.hpp"
#include "../include/PresortConfig.hpp"

// Include Visualizer APIs
#include "../include/visualizer/IArrayVisualizer.hpp"
#include "../include/visualizer/ITableVisualizer.hpp"
#include "../include/visualizer/IGraphVisualizer.hpp"
#include "../include/visualizer/VisualizationSession.hpp"

// Include Terminal Frontend
#include "../include/config/TerminalConfig.hpp"

int main() {
    bool shouldExit = false;
    while (!shouldExit) {
        AlgorithmRunner selectedAlgorithm = selectMainMenuAlgorithm(shouldExit);

        if (shouldExit) {
            break;
        }

        if (!std::cin) {
            std::cout << "Exiting application...\n";
            break;
        }

        if (!selectedAlgorithm) {
            continue;
        }

        // Gather presort configuration
        PresortConfig config = selectPresortConfig();

        // Generate data based on user pattern choice
        auto data = ArrayGenerator::generate(config.arraySize, 1, 64, config.pattern);

        // Polymorphic terminal backend instantiation
        std::unique_ptr<IArrayVisualizer> arrayVisualizer = std::make_unique<TerminalArrayVisualizer>(config.delayMs);
        std::unique_ptr<ITableVisualizer> tableVisualizer = std::make_unique<TerminalTableVisualizer>(config.delayMs);
        std::unique_ptr<IGraphVisualizer> graphVisualizer = std::make_unique<TerminalGraphVisualizer>(config.delayMs);

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
