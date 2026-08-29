#include "../include/visualizer/TerminalVisualizer.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>

TerminalVisualizer::TerminalVisualizer(int delayMs) : delayMs(delayMs) {}

void TerminalVisualizer::clearScreen() const {
#if defined(_WIN32) || defined(_WIN64)
    std::system("cls");
#else
    std::cout << "\033[2J\033[1;1H";
#endif
}

void TerminalVisualizer::renderFrame(
    const std::vector<int>& arr,
    SortEvent event,
    int idx1,
    int idx2,
    const std::string& stepName,
    const SortStats& stats)
{
    clearScreen();
    std::cout << "==== Terminal Visualizer ====\n";
    std::cout << "Step: " << stepName << "\n";
    
    // Render stats snapshot
    std::cout << "Passes: " << stats.getPasses() 
              << " | Comparisons: " << stats.getComparisons() 
              << " | Swaps: " << stats.getSwaps() << "\n\n";

    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << "[";
        if (static_cast<int>(i) == idx1 || static_cast<int>(i) == idx2) {
            std::cout << (event == SortEvent::Swap ? "!" : "*");
        } else {
            std::cout << " ";
        }
        std::cout << "] ";

        for (int v = 0; v < arr[i]; ++v) {
            std::cout << "#";
        }
        std::cout << " (" << arr[i] << ")\n";
    }

    std::cout << "\nLegend: [*] Comparing  [!] Swapping\n";
    std::fflush(stdout);

    if (delayMs > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
}